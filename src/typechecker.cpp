#include "typechecker.hpp"
#include <string>
#include <optional>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <utility>

namespace {
    struct Signature {
        std::vector<Type> param_types;
        Type retType;
    };

    struct TypeChecker {
        std::vector<std::unordered_map<std::string, Type>> scopes = { {} };
        std::unordered_map<std::string, Signature> functions;
        std::optional<Type> currentReturn;

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

        Type operator() (const FloatLiteral&) {
            return Type::Float;
        }

        Type operator() (const StringLiteral&) {
            return Type::String;
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
                    if (!isNumeric(type)) {
                        error(unary.op, "operator '-' expects an int or float operand, got " + std::string(typeName(type)));
                    }
                    return type;
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
                    if (!isNumeric(left_type) || !isNumeric(right_type) || mismatch(left_type, right_type)) {
                        error(bin.op, "operator '" + bin.op.lexeme + "' expects both int or both float operands, got " + 
                        std::string(typeName(left_type)) + " and " + std::string(typeName(right_type)));
                    }
                    return left_type;
                case TokenType::Percent:
                    if (mismatch(left_type, Type::Int) || mismatch(right_type, Type::Int)) {
                        error(bin.op, "operator '" + bin.op.lexeme + "' expects int operands, got " + std::string(typeName(left_type)) + 
                        " and " + std::string(typeName(right_type)));
                    }
                    return Type::Int;
                case TokenType::BangEqual:
                case TokenType::EqualEqual:
                    if (left_type == Type::String) {
                        error(bin.op, "cannot compare strings yet");
                    }
                    if (left_type != right_type) {
                        error(bin.op, "operator '" + bin.op.lexeme + "' expects operands of the same type, got " + std::string(typeName(left_type)) + " and " + std::string(typeName(right_type)));
                    }
                    return Type::Bool;
                case TokenType::Greater:
                case TokenType::GreaterEqual:
                case TokenType::Less:
                case TokenType::LessEqual:
                    if (!isNumeric(left_type) || !isNumeric(right_type) || mismatch(left_type, right_type)) {
                        error(bin.op, "operator '" + bin.op.lexeme + "' expects both int or both float operands, got " + std::string(typeName(left_type)) + " and " + std::string(typeName(right_type)));
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
            auto it = functions.find(call.name.lexeme);
            if (it == functions.end()) {
                error(call.name, "undefined function '" + call.name.lexeme + "'");
            }
            const Signature& sig = it->second;
            if (call.args.size() != sig.param_types.size()) {
                error(call.name, "function '" + call.name.lexeme + "' expects " + std::to_string(sig.param_types.size())
                    + " arguments, got " + std::to_string(call.args.size()));
            }
            for (size_t i = 0; i < call.args.size(); i++) {
                Type argType = check(*call.args[i]);
                if (mismatch(argType, sig.param_types[i])) {
                    error(call.name, "argument " + std::to_string(i + 1) + " of '" + call.name.lexeme + "' expects "
                        + typeName(sig.param_types[i]) + ", got " + typeName(argType));
                }
            }
            return sig.retType;
        }

        void operator() (const PrintStmt& print) {
            Type type = check(*print.expr);
            if (type == Type::Void) {
                error(print.keyword, "cannot use the result of a function without a return type");
            }
        }

        void operator() (const ExprStmt& stmt) {
            check(*stmt.expr);
        }

        void operator() (const VarStmt& var) {
            Type type = check(*var.init);
            if (type == Type::Void) {
                error(var.name, "cannot use the result of a function without a return type");
            }
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
            if (mismatch(ifType, Type::Bool)) {
                error(ifstmt.keyword, "if condition must be bool, got " + std::string(typeName(ifType)));
            }
            checkBlock(ifstmt.thenBranch);
            checkBlock(ifstmt.elseBranch);
        }

        void operator() (const WhileStmt& whilestmt) {
            Type condType = check(*whilestmt.condition);
            if (mismatch(condType, Type::Bool)) {
                error(whilestmt.keyword, "while condition must be bool, got " + std::string(typeName(condType)));
            }
            checkBlock(whilestmt.doBranch);
        }

        void operator() (const FunStmt& fun) {
            std::vector<std::unordered_map<std::string, Type>> backUp = std::move(scopes);
            scopes = {{}};
            std::optional<Type> backUpRet = currentReturn;
            currentReturn = functions[fun.name.lexeme].retType;
            for (const auto& param : fun.params) {
                scopes.back()[param.name.lexeme] = tokenToType(param.type);
            }
            checkBlock(fun.body);
            if (*currentReturn != Type::Void && !alwaysReturns(fun.body)) {
                error(fun.name, "function '" + fun.name.lexeme + "' does not return a value on every path");
            }
            scopes = std::move(backUp);
            currentReturn = backUpRet;
        }
        
        void operator() (const ReturnStmt& ret) {
            Type retType = check(*ret.value);
            if (!currentReturn) {
                error(ret.keyword, "return outside of a function");
            }
            if (*currentReturn == Type::Void) {
                error(ret.keyword, "cannot return a value from a function without a return type");
            }
            if (mismatch(retType, *currentReturn)) {
                error(ret.keyword, "function returns " + std::string(typeName(*currentReturn)) + ", got " + typeName(retType));
            }
        }

        Type check(Expr& expr) {
            Type type = std::visit(*this, expr.node);
            expr.type = type;
            return type;
        }

        bool alwaysReturns(const std::vector<Stmt>& statements) {
            for (const Stmt& stmt : statements) {
                if (std::get_if<ReturnStmt>(&stmt.node)) return true;
                if (const IfStmt* ifstmt = std::get_if<IfStmt>(&stmt.node)) {
                    if (alwaysReturns(ifstmt->thenBranch) && alwaysReturns(ifstmt->elseBranch)) return true;
                }
                if (const BlockStmt* block = std::get_if<BlockStmt>(&stmt.node)) {
                    if (alwaysReturns(block->statements)) return true;
                }
            }
            return false;
        }

        bool mismatch(Type actual, Type expected) {
            return actual != expected;
        }

        bool isNumeric(Type t) {
            return t == Type::Int || t == Type::Float;
        }

        [[noreturn]] void error(const Token& token, const std::string& message) {
            throw std::runtime_error("[line " + std::to_string(token.line) + "] Error: " + message);
        }
    };
}

void typeCheck(std::vector<Stmt>& program) {
    TypeChecker checker;
    for (Stmt& stmt : program) {
        if (const FunStmt* fun = std::get_if<FunStmt>(&stmt.node)) {
            std::vector<Type> param_types;
            for (const Param& param : fun->params) {
                param_types.push_back(tokenToType(param.type));
            }
            Type retType = fun->type ? tokenToType(*fun->type) : Type::Void;
            Signature s = Signature{std::move(param_types), retType};
            if (checker.functions.find(fun->name.lexeme) != checker.functions.end()) {
                checker.error(fun->name, "function '" + fun->name.lexeme + "' already declared");
            }
            checker.functions[fun->name.lexeme] = s;
        }
    }
    for (Stmt& stmt : program) {
        std::visit(checker, stmt.node);
    }
}
