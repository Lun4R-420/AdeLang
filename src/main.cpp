#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <memory>
#include "scanner.hpp"
#include "ast_printer.hpp"

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Could not open file '" << path << "'\n";
        std::exit(74); // I/O error
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: adec <file.adel>\n";
        return 64; // wrong usage
    }
    std::string source = readFile(argv[1]);
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    for (const Token& t : tokens) {
        std::cout << t.line << "  " << tokenTypeName(t.type) << "  '" << t.lexeme << "'\n";
    }

    auto lit123 = std::make_unique<Expr>(Expr{Literal{123}});
    auto lit45 = std::make_unique<Expr>(Expr{Literal{45}});
    auto negative = std::make_unique<Expr>(Expr{Unary{Token{TokenType::Minus, "-", 1}, std::move(lit123)}});
    auto group = std::make_unique<Expr>(Expr{Grouping{std::move(lit45)}});
    Expr root{Binary{std::move(negative), std::move(group), Token{TokenType::Star, "*", 1}}};
    std::cout << printAst(root) << '\n';

    if (scanner.hasError()) {
        return 65; // data errors
    }
    return 0;
}
