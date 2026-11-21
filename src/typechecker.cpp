#include "typechecker.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <utility>

namespace {
    struct TypeChecker {
        std::vector<std::unordered_map<std::string, Type>> scopes = { {} };

        Type lookup(const Token& name) {
            for (size_t i = scopes.size(); i >= 1; i--) {
                auto it = scopes[i - 1].find(name.lexeme);
                if (it != scopes[i - 1].end()) return it->second;
            }
            error(name, "undefined variable '" + name.lexeme + "'");
        }

        Type operator() (const Literal&) {
            return Type::Int;
        }
        Type operator() (const BoolLiteral&) {
            return Type::Bool;
        }
        Type operator() (const Grouping& group) {
            return check(*group.child);
        }
        Type operator() (const Unary& unary) {
            Type type = check(*unary.right);
            switch(unary.op.type) {
                case TokenType::Bang:
                    if (mismatch(type, Type::Bool)) {
                        error(unary.op, "operator '!' expects a bool operand, got " + std::string(typeName(type)));
                    }
                    return Type::Bool;
                case TokenType::Minus:
                    if (mismatch(type, Type::Int)) {
                        error(unary.op, "operator '-' expects an int operand, got " + std::string(typeName(type)));
                    }
                    return Type::Int;
                default:
                    error(unary.op, "unsupported unary operator '" + unary.op.lexeme + "'");
            }
        }
        Type operator() (const Binary& bin) {
            Type left_type = check(*bin.left);
            Type right_type = check(*bin.right);
            switch (bin.op.type) {
                case TokenType::Plus:
                case TokenType::Minus:
                case TokenType::Star:
                case TokenType::Slash:
                case TokenType::Percent:
                    if (mismatch(left_type, Type::Int) || mismatch(right_type, Type::Int)) {
                        error(bin.op, "operator '" + bin.op.lexeme + "' expects int operands, got " + std::string(typeName(left_type)) + " and " + std::string(typeName(right_type)));
                    }
                    return Type::Int;
                case TokenType::BangEqual:
                case TokenType::EqualEqual:
                    if (left_type != Type::Unknown && right_type != Type::Unknown && left_type != right_type) {
                        error(bin.op, "operator '" + bin.op.lexeme + "' expects operands of the same type, got " + std::string(typeName(left_type)) + " and " + std::string(typeName(right_type)));
                    }
                    return Type::Bool;
                case TokenType::Greater:
                case TokenType::GreaterEqual:
                case TokenType::Less:
                case TokenType::LessEqual:
                    if (mismatch(left_type, Type::Int) || mismatch(right_type, Type::Int)) {
                        error(bin.op, "operator '" + bin.op.lexeme + "' expects int operands, got " + std::string(typeName(left_type)) + " and " + std::string(typeName(right_type)));
                    }
                    return Type::Bool;
                default:
                    error(bin.op, "unsupported binary operator '" + bin.op.lexeme + "'");
            }
        }
        Type operator() (const Logical& logical) {
            Type left_type = check(*logical.left);
            Type right_type = check(*logical.right);
            if (mismatch(left_type, Type::Bool) || mismatch(right_type, Type::Bool)) {
                error(logical.op, "operator '" + logical.op.lexeme + "' expects bool operands, got " + std::string(typeName(left_type)) + " and " + std::string(typeName(right_type)));
            }
            return Type::Bool;
        }
        Type operator() (const Variable& var) {
            return lookup(var.name);
        }
        Type operator() (const Assign& assign) {
            Type type = check(*assign.value);
            Type declared = lookup(assign.name);
            if (mismatch(type, declared)) {
                error(assign.name, "cannot assign " + std::string(typeName(type)) + " to variable '" + assign.name.lexeme + "' of type " + typeName(declared));
            }
            return declared;
        }
        Type operator() (const Call& call) {
            for (const ExprPtr& arg : call.args) {
                check(*arg);
            }
            return Type::Unknown;
        }

        void operator() (const PrintStmt& print) {
            check(*print.expr);
        }

        void operator() (const ExprStmt& stmt) {
            check(*stmt.expr);
        }

        void operator() (const VarStmt& var) {
            Type type = check(*var.init);
            if (var.type) {
                Type declared = tokenToType(*var.type);
                if (mismatch(type, declared)) {
                    error(var.name, "variable '" + var.name.lexeme + "' declared as " + typeName(declared) + " but initialized with " + typeName(type));
                }
                type = declared;
            }
            if (scopes.back().find(var.name.lexeme) != scopes.back().end()) {
                error(var.name, "variable '" + var.name.lexeme + "' already declared");
            }
            scopes.back()[var.name.lexeme] = type;
        }

        void checkBlock(const std::vector<Stmt>& statements) {
            scopes.push_back({});
            for (const Stmt& stmt : statements) {
                std::visit(*this, stmt.node);
            }
            scopes.pop_back();
        }

        void operator() (const BlockStmt& block) {
            checkBlock(block.statements);
        }

        void operator() (const IfStmt& ifstmt) {
            Type ifType = check(*ifstmt.condition);
            checkBlock(ifstmt.thenBranch);
            checkBlock(ifstmt.elseBranch);
        }

        void operator() (const WhileStmt& whilestmt) {
            Type condType = check(*whilestmt.condition);
            checkBlock(whilestmt.doBranch);
        }

        void operator() (const FunStmt& fun) {
            std::vector<std::unordered_map<std::string, Type>> backUp = std::move(scopes);
            scopes = {{}};
            for (const auto& param : fun.params) {
                scopes.back()[param.name.lexeme] = tokenToType(param.type);
            }
            checkBlock(fun.body);
            scopes = std::move(backUp);
        }
        
        void operator() (const ReturnStmt& ret) {
            Type retType = check(*ret.value);
        }

        Type check(Expr& expr) {
            Type type = std::visit(*this, expr.node);
            expr.type = type;
            return type;
        }

        bool mismatch(Type actual, Type expected) {
            return actual != Type::Unknown && actual != expected;
        }

        [[noreturn]] void error(const Token& token, const std::string& message) {
            throw std::runtime_error("[line " + std::to_string(token.line) + "] Error: " + message);
        }
    };
}

void typeCheck(std::vector<Stmt>& program) {
    TypeChecker checker;
    for (Stmt& stmt : program) {
        std::visit(checker, stmt.node);
    }
}
