#include <iostream>
#include "scanner.hpp"

int main() {
    std::string source = "var x1 = 42;\nwhile my_var \"hello\" @ \"oops";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    for (const Token& t : tokens) {
        std::cout << t.line << "  " << tokenTypeName(t.type) << "  '" << t.lexeme << "'\n";
    }
    if (scanner.hasError()) {
        return 65;
    }
    return 0;
}
