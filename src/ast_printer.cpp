#include "ast_printer.hpp"

struct AstPrinter {
    std::string operator() (const Literal& lit) {
        return std::to_string(lit.number);
    }
    std::string operator() (const Unary& unary) {
        std::string s = "(" + unary.op.lexeme + " " + printAst(*unary.right) + ")";
        return s;
    }
    std::string operator() (const Binary& binary) {
        std::string s = "(" + binary.op.lexeme + " " + printAst(*binary.left) + " " + printAst(*binary.right) + ")";
        return s;
    }
    std::string operator() (const Grouping& group) {
        std::string s = "(group " + printAst(*group.child) + ")";
        return s;
    }
    std::string operator() (const Variable&) {
        return "";
    }
    std::string operator() (const Assign&) {
        return "";
    }
};

std::string printAst(const Expr& expr) {
    return std::visit(AstPrinter{}, expr.node);
}
