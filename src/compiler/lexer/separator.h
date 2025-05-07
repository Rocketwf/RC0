#pragma once

#include <string>
#include <unordered_map>

#include "token.h"
#include "../span.h"

class Separator: public Token {
    public:
        enum class Separator_type {
        PAR_OPEN,
        PAR_CLOSE,
        BRACE_OPEN,
        BRACE_CLOSE,
        SEMICOLON
    };
    Separator(Separator_type type, Span span):
        m_type(type),
        m_span(span) {}
    std::unordered_map<Separator_type, std::string> separators = {
        {Separator_type::PAR_OPEN, "("},
        {Separator_type::PAR_CLOSE, ")"},
        {Separator_type::BRACE_OPEN, "{"},
        {Separator_type::BRACE_CLOSE, "}"}
    };
    std::string asString() override {
            return separators[m_type];
    }
    private: 
    Separator_type m_type;
    Span m_span;
};