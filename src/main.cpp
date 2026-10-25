#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include "scanner.hpp"
#include "parser.hpp"
#include "codegen.hpp"

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

void writeFile(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    if (!file) {
        std::cerr << "Could not write file '" << path << "'\n";
        std::exit(73);
    }
    file << content;
}

int main(int argc, char* argv[]) {
    if (argc != 4 || std::string(argv[2]) != "-o") {
        std::cerr << "Usage: adec <file.adel> -o <output>\n";
        return 64; // wrong usage
    }
    std::string inputPath = argv[1];
    std::string outputPath = argv[3];
    std::string asmPath = outputPath + ".s";

    std::string source = readFile(inputPath);
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    if (scanner.hasError()) {
        return 65; // data errors
    }

    Parser parser(tokens);
    std::string assembly;
    try {
        std::vector<Stmt> program = parser.parse();
        assembly = generateProgram(program);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return 65;
    }

    writeFile(asmPath, assembly);

    std::string command = "gcc \"" + asmPath + "\" -o \"" + outputPath + "\"";
    if (std::system(command.c_str()) != 0) {
        std::cerr << "Error: assembling or linking failed\n";
        return 70;
    }
    return 0;
}
