#include "codegen.hpp"
#include <unordered_map>
#include <sstream>
#include <stdexcept>

namespace {
    struct CodeGen {
        std::ostringstream out;
        std::vector<std::unordered_map<std::string, int>> scopes{ {} };
        int stackSize = 0;
        int labelCount = 0;
        
        int lookup(const Token& name) {
            for (size_t i = scopes.size(); i >= 1; i--) {
                auto it = scopes[i - 1].find(name.lexeme);
                if (it != scopes[i - 1].end()) return it->second;
            }
            throw std::runtime_error("[line " + std::to_string(name.line) + "] Error: undefined variable '" + name.lexeme + "'");
        }

        void genBlock(const std::vector<Stmt>& statements) {
            scopes.push_back({});
            for (const Stmt& stmt : statements) {
                std::visit(*this, stmt.node);
            }
            scopes.pop_back();
        }

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
            int offset = lookup(v.name);
            emit("movq " + std::to_string(offset) + "(%rbp), %rax");
        }

        void operator()(const Assign& assign) {
            std::visit(*this, assign.value->node);
            int offset = lookup(assign.name);
            emit("movq %rax, " + std::to_string(offset) + "(%rbp)");
        }

        void operator()(const VarStmt& var) {
            std::visit(*this, var.init->node);
            if (scopes.back().find(var.name.lexeme) != scopes.back().end()) {
                throw std::runtime_error("[line " + std::to_string(var.name.line) + "] Error: variable '" + var.name.lexeme + "' already declared");
            }
            stackSize += 8;
            scopes.back()[var.name.lexeme] = -stackSize;
            emit("movq %rax, " + std::to_string(-stackSize) + "(%rbp)");
        }

        void operator()(const BlockStmt& block) {
            genBlock(block.statements);
        }

        void operator()(const IfStmt& ifstmt) {
            int id = labelCount++;
            std::visit(*this, ifstmt.condition->node);
            emit("cmpq $0, %rax");
            emit("je .Lelse_" + std::to_string(id));
            genBlock(ifstmt.thenBranch);
            emit("jmp .Lend_" + std::to_string(id));
            out << ".Lelse_" + std::to_string(id) + ":\n";
            genBlock(ifstmt.elseBranch);
            out << ".Lend_" + std::to_string(id) + ":\n";
        }
    };
}

std::string generateProgram(const std::vector<Stmt>& program) {
    CodeGen gen;
    for (const Stmt& stmt : program) {
        std::visit(gen, stmt.node);
    }
    std::string body = gen.out.str();
    int frameSize = (gen.stackSize + 15) / 16 * 16;

    std::ostringstream result;
    result << ".section .rodata\nfmt: .string \"%lld\\n\"\n.text\n.globl main\nmain:\n";
    result << "    pushq %rbp\n";
    result << "    movq %rsp, %rbp\n";
    if (frameSize > 0) {
        result << "    subq $" << frameSize << ", %rsp\n";
    }
    result << body;
    result << "    movl $0, %eax\n";
    result << "    movq %rbp, %rsp\n";
    result << "    popq %rbp\n";
    result << "    ret\n";
    result << ".section .note.GNU-stack,\"\",@progbits\n";
    return result.str();
}