#pragma once

#include <string>
#include <unordered_map>

#include "token.h"
#include "../span.h"
#include "separator_type.h"

class Separator: public Token {
    public:
    bool is_separator(SeparatorType separator_type) const override {
        return get_type() == separator_type;
    }

    Separator(SeparatorType type, Span span):
        Token(span),
        m_type(type) {}
    const std::unordered_map<SeparatorType, std::string> separators = {
        {SeparatorType::PAR_OPEN, "("},
        {SeparatorType::PAR_CLOSE, ")"},
        {SeparatorType::BRACE_OPEN, "{"},
        {SeparatorType::BRACE_CLOSE, "}"},
        {SeparatorType::SEMICOLON, ";"}};
    std::string as_string() const override {
            return separators.at(m_type);
    }
    SeparatorType get_type() const { return m_type; }
    TokenType token_type() override { return TokenType::SEPARATOR; }
    private: 
    SeparatorType m_type;
};