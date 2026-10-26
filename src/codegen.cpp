#include "codegen.hpp"
#include <unordered_map>
#include <sstream>
#include <stdexcept>

namespace {
    struct CodeGen {
        std::ostringstream out;
        std::unordered_map<std::string, int> locals;
        int stackSize = 0;
        void emit(const std::string& line) {
            out << "    " << line << '\n';
        }

        void compare(const std::string& setInstr) {
            emit("cmpq %rcx, %rax");
            emit(setInstr + " %al");
            emit("movzbq %al, %rax");
        }

        void operator()(const Literal& lit) {
            std::string instr = "movq $" + std::to_string(lit.number) + ", %rax";
            emit(instr);
        }

        void operator()(const Unary& unary) {
            std::visit(*this, unary.right->node);
            switch (unary.op.type) {
                case TokenType::Minus:
                    emit("negq %rax");
                    break;
                case TokenType::Bang:
                    emit("cmpq $0, %rax");
                    emit("sete %al");
                    emit("movzbq %al, %rax");
                    break;
                default:
                    throw std::runtime_error("[line " + std::to_string(unary.op.line) + "] Error: unsupported unary operator '" + unary.op.lexeme + "'");
            }
        }

        void operator()(const Binary& bin) {
            std::visit(*this, bin.left->node);
            emit("pushq %rax");
            std::visit(*this, bin.right->node);
            emit("movq %rax, %rcx");
            emit("popq %rax");
            switch (bin.op.type) {
                case TokenType::Plus:
                    emit("addq %rcx, %rax");
                    break;
                case TokenType::Minus:
                    emit("subq %rcx, %rax");
                    break;
                case TokenType::Star:
                    emit("imulq %rcx, %rax");
                    break;
                case TokenType::Slash:
                    emit("cqto");
                    emit("idivq %rcx");
                    break;
                case TokenType::Percent:
                    emit("cqto");
                    emit("idivq %rcx");
                    emit("movq %rdx, %rax");
                    break;
                case TokenType::EqualEqual:
                    compare("sete");
                    break;
                case TokenType::BangEqual:
                    compare("setne");
                    break;
                case TokenType::Greater:
                    compare("setg");
                    break;
                case TokenType::GreaterEqual:
                    compare("setge");
                    break;
                case TokenType::Less:
                    compare("setl");
                    break;
                case TokenType::LessEqual:
                    compare("setle");
                    break;
                default:
                    throw std::runtime_error("[line " + std::to_string(bin.op.line) + "] Error: unsupported binary operator '" + bin.op.lexeme + "'");
            }
        }

        void operator()(const Grouping& group) {
            std::visit(*this, group.child->node);
        }

        void operator()(const PrintStmt& print) {
            std::visit(*this, print.expr->node);
            emit("movq %rax, %rsi");
            emit("leaq fmt(%rip), %rdi");
            emit("movl $0, %eax");
            emit("call printf@PLT");
        }

        void operator()(const ExprStmt& stmt) {
            std::visit(*this, stmt.expr->node);
        }

        void operator()(const Variable& v) {
            auto it = locals.find(v.name.lexeme);
            if (it == locals.end()) {
                throw std::runtime_error("[line " + std::to_string(v.name.line) + "] Error: undefined variable '" + v.name.lexeme + "'");
            }
            emit("movq " + std::to_string(it->second) + "(%rbp), %rax");
        }

        void operator()(const Assign& assign) {
            std::visit(*this, assign.value->node);
            auto it = locals.find(assign.name.lexeme);
            if (it == locals.end()) {
                throw std::runtime_error("[line " + std::to_string(assign.name.line) + "] Error: undefined variable '" + assign.name.lexeme + "'");
            }
            emit("movq %rax, " + std::to_string(it->second) + "(%rbp)");
        }

        void operator()(const VarStmt& var) {
            if (locals.find(var.name.lexeme) != locals.end()) {
                throw std::runtime_error("[line " + std::to_string(var.name.line) + "] Error: variable '" + var.name.lexeme + "' already declared");
            }
            std::visit(*this, var.init->node);
            stackSize += 8;
            locals[var.name.lexeme] = -stackSize;
            emit("movq %rax, " + std::to_string(-stackSize) + "(%rbp)");
        }
    };
}

std::string generateProgram(const std::vector<Stmt>& program) {
    CodeGen gen;
    int frameSize = 0;
    for (const Stmt& stmt : program) {
        if (std::holds_alternative<VarStmt>(stmt.node)) frameSize += 8;
    }
    frameSize = (frameSize + 15) / 16 * 16;

    gen.out << ".section .rodata\nfmt: .string \"%lld\\n\"\n.text\n.globl main\nmain:\n";
    gen.emit("pushq %rbp");
    gen.emit("movq %rsp, %rbp");
    gen.emit("subq $" + std::to_string(frameSize) + ", %rsp");
    for (const Stmt& stmt : program) {
        std::visit(gen, stmt.node);
    }
    gen.emit("movl $0, %eax");
    gen.emit("movq %rbp, %rsp");
    gen.emit("popq %rbp");
    gen.emit("ret");
    gen.out << ".section .note.GNU-stack,\"\",@progbits\n";
    return gen.out.str();
}