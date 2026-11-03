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
    return assignment();
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
    if (match({TokenType::Identifier})) {
        Token name = previous();
        if (match({TokenType::LeftParen})) {
            std::vector<ExprPtr> args;
            if (!check(TokenType::RightParen)) {
                do {
                    if (args.size() >= 6) {
                        throw std::runtime_error("[line " + std::to_string(peek().line) + "] Error: functions can have at most 6 parameters");
                    }
                    args.push_back(expression());
                } while(match({TokenType::Comma}));
            }
            consume(TokenType::RightParen, "expected ')' after arguments");
            return std::make_unique<Expr>(Expr{Call{name, std::move(args)}});
        }
        return std::make_unique<Expr>(Expr{Variable{name}});
    }
    throw std::runtime_error("[line " + std::to_string(peek().line) + "] Error: expected expression");
}

ExprPtr Parser::assignment() {
    ExprPtr target = equality();
    if (match({TokenType::Equal})) {
        Token equals = previous();
        ExprPtr value = assignment();
        if (auto* var = std::get_if<Variable>(&target->node)) {
            Token name = var->name;
            return std::make_unique<Expr>(Expr{Assign{name, std::move(value)}});
        } else {
            throw std::runtime_error("[line " + std::to_string(equals.line) + "] Error: invalid assignment target");
        }
    }
    return target;
}

Stmt Parser::statement() {
    if (match({TokenType::Print})) {
        return printStatement();
    }
    if (match({TokenType::LeftBrace})) {
        return Stmt{BlockStmt{block()}};
    }
    if (match({TokenType::If})) {
        return ifStatement();
    }
    if (match({TokenType::While})) {
        return whileStatement();
    }
    if (match({TokenType::Return})) {
        return returnStatement();
    }
    return expressionStatement();
}

Stmt Parser::printStatement() {
    ExprPtr value = expression();
    consume(TokenType::Semicolon, "expected ';' after expression");
    return Stmt{PrintStmt{std::move(value)}};
}

Stmt Parser::expressionStatement() {
    ExprPtr value = expression();
    consume(TokenType::Semicolon, "expected ';' after expression");
    return Stmt{ExprStmt{std::move(value)}};
}

Stmt Parser::declaration() {
    if (match({TokenType::Var})) {
        return varDeclaration();
    }
    if (match({TokenType::Fun})) {
        return funDeclaration();
    }
    return statement();
}

Stmt Parser::varDeclaration() {
    Token name = consume(TokenType::Identifier, "expected variable name");
    consume(TokenType::Equal, "expected '=' after variable name");
    ExprPtr init = expression();
    consume(TokenType::Semicolon, "expected ';' after variable expression");
    return Stmt{VarStmt{name, std::move(init)}};
}

std::vector<Stmt> Parser::block() {
    std::vector<Stmt> statements;
    while (!isAtEnd() && peek().type != TokenType::RightBrace) {
        statements.push_back(declaration());
    }
    consume(TokenType::RightBrace, "expected '}' after block");
    return statements;
}

Stmt Parser::ifStatement() {
    ExprPtr condition = expression();
    consume(TokenType::LeftBrace, "expected '{' after if condition");
    std::vector<Stmt> thenBranch = block();
    std::vector<Stmt> elseBranch;
    if (match({TokenType::Else})) {
        if (match({TokenType::If})) {
            elseBranch.push_back(ifStatement());
        } else {
            consume(TokenType::LeftBrace, "expected '{' after else");
            elseBranch = block();
        }
    }
    return Stmt{IfStmt{std::move(condition), std::move(thenBranch), std::move(elseBranch)}};
}

Stmt Parser::whileStatement() {
    ExprPtr condition = expression();
    consume(TokenType::LeftBrace, "expected '{' after while condition");
    std::vector<Stmt> doBranch = block();
    return Stmt{WhileStmt{std::move(condition), std::move(doBranch)}};
}

std::vector<Stmt> Parser::parse() {
    std::vector<Stmt> statements;
    while (!isAtEnd()) {
        statements.push_back(declaration());
    }
    return statements;
}

Stmt Parser::funDeclaration() {
    Token name = consume(TokenType::Identifier, "expected function name");
    consume(TokenType::LeftParen, "expected '(' after function name");
    std::vector<Token> params;
    if (!check(TokenType::RightParen)) {
        do {
            Token param = consume(TokenType::Identifier, "expected parameter name");
            consume(TokenType::Colon, "expected ':' after parameter name");
            consume(TokenType::Identifier, "expected parameter type");
            if (params.size() >= 6) {
                throw std::runtime_error("[line " + std::to_string(param.line) + "] Error: functions can have at most 6 parameters");
            }
            params.push_back(param);
        } while (match({TokenType::Comma}));
    }
    consume(TokenType::RightParen, "expected ')' after parameters");
    if (match({TokenType::Arrow})) {
        consume(TokenType::Identifier, "expected return type");
    }
    consume(TokenType::LeftBrace, "expected '{' before function body");
    std::vector<Stmt> body = block();
    return Stmt{FunStmt{std::move(name), std::move(params), std::move(body)}};
}

Stmt Parser::returnStatement() {
    Token keyword = previous();
    ExprPtr value = expression();
    consume(TokenType::Semicolon, "expected ';' after return value");
    return Stmt{ReturnStmt{keyword, std::move(value)}};
}
