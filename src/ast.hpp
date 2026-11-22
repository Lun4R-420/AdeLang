#pragma once
#include "token.hpp"
#include "types.hpp"
#include <memory>
#include <variant>
#include <vector>
#include <optional>

struct Expr;
using ExprPtr = std::unique_ptr<Expr>;
struct Stmt;

struct Param {
    Token name;
    Token type;
};

struct Literal {
    long long number;
};

struct FloatLiteral {
    double value;
};

struct StringLiteral {
    std::string value;
};

struct Unary {
    Token op;
    std::unique_ptr<Expr> right;
};

struct Binary {
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    Token op;
};

struct Logical {
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    Token op;
};

struct Grouping {
    std::unique_ptr<Expr> child;
};

struct Variable {
    Token name;
};

struct Assign {
    Token name;
    ExprPtr value;
};

struct Call {
    Token name;
    std::vector<ExprPtr> args;
};

struct BoolLiteral {
    bool value;
};

struct Expr {
    std::variant<Literal, FloatLiteral, StringLiteral, BoolLiteral, Unary, Binary, Logical, Grouping, Variable, Assign, Call> node;
    Type type = Type::Unknown;
};

struct VarStmt {
    Token name;
    ExprPtr init;
    std::optional<Token> type;
};

struct PrintStmt {
    Token keyword;
    ExprPtr expr;
};

struct ExprStmt {
    ExprPtr expr;
};

struct BlockStmt {
    std::vector<Stmt> statements;
};

struct IfStmt {
    Token keyword;
    ExprPtr condition;
    std::vector<Stmt> thenBranch;
    std::vector<Stmt> elseBranch;
};

struct WhileStmt {
    Token keyword;
    ExprPtr condition;
    std::vector<Stmt> doBranch;
};

struct FunStmt {
    Token name;
    std::vector<Param> params;
    std::vector<Stmt> body;
    std::optional<Token> type;
};

struct ReturnStmt {
    Token keyword;
    ExprPtr value;
};

struct Stmt {
    std::variant<PrintStmt, ExprStmt, VarStmt, BlockStmt, IfStmt, WhileStmt, FunStmt, ReturnStmt> node;
};
