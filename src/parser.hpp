#pragma once
#include <vector>
#include <initializer_list>
#include "token.hpp"
#include "ast.hpp"

class Parser {
private:
    std::vector<Token> tokens;
    size_t current = 0;

    const Token& peek();
    const Token& previous();
    bool isAtEnd();
    Token advance();
    bool check(TokenType type);
    bool match(std::initializer_list<TokenType> tokenList);
    const Token& consume(TokenType type, const std::string& message);
    ExprPtr expression();
    ExprPtr equality();
    ExprPtr comparison();
    ExprPtr term();
    ExprPtr factor();
    ExprPtr unary();
    ExprPtr primary();

public:
    Parser(std::vector<Token> tokens);

    ExprPtr parse();
};
