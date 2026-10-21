#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include "scanner.hpp"
#include "parser.hpp"
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
    if (scanner.hasError()) {
        return 65; // data errors
    }

    Parser parser(tokens);
    try {
        ExprPtr ast = parser.parse();
        std::cout << printAst(*ast) << '\n';
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return 65;
    }
    return 0;
}
