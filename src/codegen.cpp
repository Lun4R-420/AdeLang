#include "codegen.hpp"
#include <unordered_map>
#include <sstream>
#include <stdexcept>

static const std::vector<std::string> argRegs = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};

namespace {
    struct CodeGen {
        std::ostringstream out;
        std::vector<std::unordered_map<std::string, int>> scopes{ {} };
        std::unordered_map<std::string, size_t> table;
        std::string returnLabel;
        bool inFunction = false;
        int stackSize = 0;
        int labelCount = 0;
        int pushDepth = 0;

        void push() {
            emit("pushq %rax");
            pushDepth++;
        }

        void pop(const std::string& reg) {
            emit("popq " + reg);
            pushDepth--;
        }
        
        void emitCall(const std::string& target) {
            bool pad = pushDepth % 2 != 0;
            if (pad) emit("subq $8, %rsp");
            emit("call " + target);
            if (pad) emit("addq $8, %rsp");
        }

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
            push();
            std::visit(*this, bin.right->node);
            emit("movq %rax, %rcx");
            pop("%rax");
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
            emitCall("printf@PLT");
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

        void operator()(const WhileStmt& whilestmt) {
            int id = labelCount++;
            out << ".Lwhile_" + std::to_string(id) + ":\n";
            std::visit(*this, whilestmt.condition->node);
            emit("cmpq $0, %rax");
            emit("je .Lwend_" + std::to_string(id));
            genBlock(whilestmt.doBranch);
            emit("jmp .Lwhile_" + std::to_string(id));
            out << ".Lwend_" + std::to_string(id) + ":\n";
        }

        void operator()(const Call& call) {
            auto it = table.find(call.name.lexeme);
            if (it == table.end()) {
                throw std::runtime_error("[line " + std::to_string(call.name.line) + "] Error: undefined function '" + call.name.lexeme + "'");
            }

            if (it->second != call.args.size()) {
                throw std::runtime_error("[line " + std::to_string(call.name.line) + "] Error: function '" + call.name.lexeme + "' expects "
            + std::to_string(it->second) + " arguments, got " + std::to_string(call.args.size()));
            }

            for (const ExprPtr& arg : call.args) {
                std::visit(*this, arg->node);
                push();
            }
            for (size_t i = call.args.size(); i > 0; i--) {
                pop(argRegs[i - 1]);
            }
            emitCall("ade_" + call.name.lexeme);
        }

        void operator()(const FunStmt& fun) {
            throw std::runtime_error("[line " + std::to_string(fun.name.line) + "] Error: functions must be declared at the top level");
        }

        void operator()(const ReturnStmt& ret) {
            if (!inFunction) {
                throw std::runtime_error("[line " + std::to_string(ret.keyword.line) + "] Error: return outside of a function");
            }
            std::visit(*this, ret.value->node);
            emit("jmp " + returnLabel);
        }
    };
}

std::string generateFunction(const std::string& label, const std::vector<const Stmt*>& body, const std::vector<Param>& params, int& labelCount,
                            const std::unordered_map<std::string, size_t>& table) {
    CodeGen gen;
    gen.returnLabel = ".Lret_" + label;
    gen.inFunction = label == "main" ? false : true;
    gen.labelCount = labelCount;
    gen.table = table;

    for (size_t i = 0; i < params.size(); i++) {
        gen.stackSize += 8;
        gen.scopes.back()[params[i].name.lexeme] = -gen.stackSize;
        gen.emit("movq " + argRegs[i] + ", " + std::to_string(-gen.stackSize) + "(%rbp)");
    }

    for (const Stmt* stmt : body) {
        std::visit(gen, stmt->node);
    }
    labelCount = gen.labelCount;
    std::string func_body = gen.out.str();
    int frameSize = (gen.stackSize + 15) / 16 * 16;

    std::ostringstream result;
    result << label + ":\n";
    result << "    pushq %rbp\n";
    result << "    movq %rsp, %rbp\n";
    
    if (frameSize > 0) {
        result << "    subq $" << frameSize << ", %rsp\n";
    }

    result << func_body;
    result << "    movq $0, %rax\n";
    result << gen.returnLabel + ":\n";
    result << "    movq %rbp, %rsp\n";
    result << "    popq %rbp\n";
    result << "    ret\n";
    
    return result.str();
}

std::string generateProgram(const std::vector<Stmt>& program) {
    std::vector<const FunStmt*> functions;
    std::vector<const Stmt*> topLevel;
    std::unordered_map<std::string, size_t> function_table;
    for (const Stmt& stmt : program) {
        if (const FunStmt* fun = std::get_if<FunStmt>(&stmt.node)) {
            functions.push_back(fun);
            if (function_table.find(fun->name.lexeme) != function_table.end()) {
                throw std::runtime_error("[line " + std::to_string(fun->name.line) + "] Error: function '" + fun->name.lexeme + "' already declared");
            }
            function_table[fun->name.lexeme] = fun->params.size();
        } else {
            topLevel.push_back(&stmt);
        }
    }

    int labelCount = 0;
    std::ostringstream result;
    result << ".section .rodata\nfmt: .string \"%lld\\n\"\n.text\n.globl main\n";

    for (const FunStmt* fun : functions) {
        std::vector<const Stmt*> body;
        for (const Stmt& stmt : fun->body) {
            body.push_back(&stmt);
        }
        result << generateFunction("ade_" + fun->name.lexeme, body, fun->params, labelCount, function_table);
    }

    result << generateFunction("main", topLevel, {}, labelCount, function_table);
    result << ".section .note.GNU-stack,\"\",@progbits\n";
    return result.str();
}