#pragma once
#include "token.hpp"

enum class Type {
    Int, Float, String, Bool, Void, Unknown
};

const char* typeName(Type type);
Type tokenToType(const Token& token);