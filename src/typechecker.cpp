#include "typechecker.hpp"
#include <string>
#include <vector>
#include <stdexcept>

namespace {
    struct TypeChecker {
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
        Type operator() (const Variable&) {
            return Type::Unknown;
        }
        Type operator() (const Assign& assign) {
            Type type = check(*assign.value);
            return Type::Unknown;
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
        }

        void checkBlock(const std::vector<Stmt>& statements) {
            for (const Stmt& stmt : statements) {
                std::visit(*this, stmt.node);
            }
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
            checkBlock(fun.body);
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
