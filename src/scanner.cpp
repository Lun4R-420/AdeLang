#include <cctype>
#include <iostream>
#include <unordered_map>
#include "scanner.hpp"

static bool isDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

static bool isAlpha(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
}

static bool isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

static const std::unordered_map<std::string, TokenType> keywords = {
    {"and", TokenType::And},
    {"else", TokenType::Else},
    {"false", TokenType::False},
    {"fun", TokenType::Fun},
    {"for", TokenType::For},
    {"if", TokenType::If},
    {"or", TokenType::Or},
    {"print", TokenType::Print},
    {"return", TokenType::Return},
    {"true", TokenType::True},
    {"var", TokenType::Var},
    {"while", TokenType::While},
};

Scanner::Scanner(std::string source) : source(source) {}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

char Scanner::advance() {
    return source[current++];
}

void Scanner::scanToken() {
    char c = advance();
    switch(c) {
        case '(': addToken(TokenType::LeftParen); break;
        case ')': addToken(TokenType::RightParen); break;
        case '[': addToken(TokenType::LeftBracket); break;
        case ']': addToken(TokenType::RightBracket); break;
        case '{': addToken(TokenType::LeftBrace); break;
        case '}': addToken(TokenType::RightBrace); break;
        case ',': addToken(TokenType::Comma); break;
        case '.': addToken(TokenType::Dot); break;
        case '-': 
            if (match('>')) {
                addToken(TokenType::Arrow);
            } else {
                addToken(TokenType::Minus);
            }
            break;
        case '+': addToken(TokenType::Plus); break;
        case ';': addToken(TokenType::Semicolon); break;
        case ':': addToken(TokenType::Colon); break;
        case '/': 
            if (match('/')) {
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType::Slash);
            }
            break;
        case '!':
            if (match('=')) {
                addToken(TokenType::BangEqual);
            } else {
                addToken(TokenType::Bang);
            }
            break;
        case '=':
            if (match('=')) {
                addToken(TokenType::EqualEqual);
            } else {
                addToken(TokenType::Equal);
            }
            break;
        case '>':
            if (match('=')) {
                addToken(TokenType::GreaterEqual);
            } else {
                addToken(TokenType::Greater);
            }
            break;
        case '<':
            if (match('=')) {
                addToken(TokenType::LessEqual);
            } else {
                addToken(TokenType::Less);
            }
            break;
        
        case '*': addToken(TokenType::Star); break;
        case '%': addToken(TokenType::Percent); break;
        case '"': string(); break;
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n': line++; break;
        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                std::cerr << "[line " << line << "] Error: unexpected character '" << c << "'\n";
                hadError = true;    
            }
            break;
    }
}

void Scanner::addToken(TokenType type) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token{type, text, line});
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;
    
    current++;
    return true;
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Scanner::peekNext() {
    if (isAtEnd() || current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        std::cerr << "[line " << line << "] Error: unterminated string\n";
        hadError = true;
        return;
    }

    advance();

    addToken(TokenType::String);
}

void Scanner::number() {
    while (isDigit(peek())) advance();

    // if (peek() == '.' && isdigit(peekNext())) {
    //     advance();

    //     while (isdigit(peek())) advance();
    // }

    addToken(TokenType::Number);
}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();

    std::string text = source.substr(start, current - start);
    auto it = keywords.find(text);
    addToken(it != keywords.end() ? it->second : TokenType::Identifier);
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back(Token{TokenType::Eof, "", line});
    return tokens;
}

bool Scanner::hasError() {
    return hadError;
}
