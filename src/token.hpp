#pragma once
#include <string>

enum class TokenType {
    LeftParen, RightParen, LeftBracket, RightBracket, LeftBrace, RightBrace, Comma, Dot, Minus, Plus, Semicolon, Slash, Star, Percent, Colon,
    Arrow, Bang, BangEqual, Equal, EqualEqual, Greater, GreaterEqual, Less, LessEqual,
    Identifier, String, Number,
    And, Else, False, Fun, For, If, Or, Print, Return, True, Var, While,
    Eof
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

const char* tokenTypeName(TokenType type);
