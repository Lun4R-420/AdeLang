#include <stdexcept>
#include "parser.hpp"

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {}

const Token& Parser::peek() {
    return tokens[current];
}

const Token& Parser::previous() {
    return tokens[current - 1];
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::Eof;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

bool Parser::check(TokenType type) {
    if (peek().type == type) return true;
    return false;
}

bool Parser::match(std::initializer_list<TokenType> tokenList) {
    if (isAtEnd()) return false;

    for (auto& type : tokenList) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

const Token& Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) {
        advance();
        return previous();
    }
    throw std::runtime_error("[line " + std::to_string(peek().line) + "] Error: " + message);
}

ExprPtr Parser::expression() {
    return equality();
}

ExprPtr Parser::equality() {
    ExprPtr left = comparison();
    while (match({TokenType::EqualEqual, TokenType::BangEqual})) {
        Token op = previous();
        ExprPtr right = comparison();
        left = std::make_unique<Expr>(Expr{Binary{std::move(left), std::move(right), op}});
    }
    return left;
}

ExprPtr Parser::comparison() {
    ExprPtr left = term();
    while (match({TokenType::Greater, TokenType::GreaterEqual, TokenType::Less, TokenType::LessEqual})) {
        Token op = previous();
        ExprPtr right = term();
        left = std::make_unique<Expr>(Expr{Binary{std::move(left), std::move(right), op}});
    }
    return left;
}

ExprPtr Parser::term() {
    ExprPtr left = factor();
    while (match({TokenType::Plus, TokenType::Minus})) {
        Token op = previous();
        ExprPtr right = factor();
        left = std::make_unique<Expr>(Expr{Binary{std::move(left), std::move(right), op}});
    }
    return left;
}

ExprPtr Parser::factor() {
    ExprPtr left = unary();
    while (match({TokenType::Star, TokenType::Slash, TokenType::Percent})) {
        Token op = previous();
        ExprPtr right = unary();
        left = std::make_unique<Expr>(Expr{Binary{std::move(left), std::move(right), op}});
    }
    return left;
}

ExprPtr Parser::unary() {
    if (match({TokenType::Bang, TokenType::Minus})) {
        Token op = previous();
        ExprPtr right = unary();
        return std::make_unique<Expr>(Expr{Unary{op, std::move(right)}});
    }
    return primary();
}

ExprPtr Parser::primary() {
    if (match({TokenType::Number})) {
        try {
            return std::make_unique<Expr>(Expr{Literal{std::stoll(previous().lexeme)}});
        } catch (const std::out_of_range&) {
            throw std::runtime_error("[line " + std::to_string(previous().line) + "] Error: number literal too large");
        }
    }
    if (match({TokenType::LeftParen})) {
        ExprPtr inner = expression();
        consume(TokenType::RightParen, "expected ')' after expression");
        return std::make_unique<Expr>(Expr{Grouping{std::move(inner)}});
    }
    throw std::runtime_error("[line " + std::to_string(peek().line) + "] Error: expected expression");
}

ExprPtr Parser::parse() {
    ExprPtr expr = expression();
    consume(TokenType::Eof, "expected end of expression");
    return expr;
}
