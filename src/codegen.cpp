#include "codegen.hpp"
#include <sstream>
#include <stdexcept>

namespace {
    struct CodeGen {
        std::ostringstream out;
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
    };
}

std::string generateProgram(const Expr& expr) {
    CodeGen gen;
    gen.out << ".text\n.globl main\nmain:\n";
    std::visit(gen, expr.node);
    gen.emit("ret");
    gen.out << ".section .note.GNU-stack,\"\",@progbits\n";
    return gen.out.str();
}