#include "types.hpp"
#include <string>
#include <unordered_map>
#include <stdexcept>

const char* typeName(Type type) {
    switch (type) {
        case Type::Int: 
            return "int";
        case Type::Float:
            return "float";
        case Type::Bool:
            return "bool";
        case Type::Void:
            return "void";
        case Type::Unknown:
            return "unknown";
    }
    return "";
}

static const std::unordered_map<std::string, Type> typeNames = {
    {"int", Type::Int},
    {"float", Type::Float},
    {"bool", Type::Bool}
};

Type tokenToType(const Token& token) {
    auto it = typeNames.find(token.lexeme);
    if (it != typeNames.end()) return it->second;
    throw std::runtime_error("[line " + std::to_string(token.line) + "] Error: unknown type '" + token.lexeme + "'");
}