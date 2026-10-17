#pragma once
#include "token.hpp"
#include <vector>

class Scanner {
private:
    std::string source;
    std::vector<Token> tokens;

    size_t start = 0;
    size_t current = 0;
    int line = 1;
    bool hadError = false;

    bool isAtEnd();
    char advance();
    void scanToken();
    void addToken(TokenType type);
    bool match(char expected);
    char peek();
    char peekNext();
    void string();
    void number();
    void identifier();
public:
    Scanner(std::string source);

    std::vector<Token> scanTokens();
    bool hasError();
};

