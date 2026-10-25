#pragma once
#include "token.hpp"
#include <memory>
#include <variant>

struct Expr;
using ExprPtr = std::unique_ptr<Expr>;
struct Stmt;

struct Literal {
    long long number;
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

struct Expr {
    std::variant<Literal, Unary, Binary, Grouping, Variable, Assign> node;
};

struct VarStmt {
    Token name;
    ExprPtr init;
};

struct PrintStmt {
    ExprPtr expr;
};

struct ExprStmt {
    ExprPtr expr;
};

struct Stmt {
    std::variant<PrintStmt, ExprStmt, VarStmt> node;
};
