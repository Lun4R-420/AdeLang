#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "scanner.hpp"

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
        std::cerr << "Usage: adec <file.ade>\n";
        return 64; // wrong usage
    }
    std::string source = readFile(argv[1]);
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    for (const Token& t : tokens) {
        std::cout << t.line << "  " << tokenTypeName(t.type) << "  '" << t.lexeme << "'\n";
    }
    if (scanner.hasError()) {
        return 65; // data errors
    }
    return 0;
}
