#pragma once
#include "token.hpp"
#include <memory>
#include <variant>

struct Expr;

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

struct Expr {
    std::variant<Literal, Unary, Binary, Grouping> node;
};
