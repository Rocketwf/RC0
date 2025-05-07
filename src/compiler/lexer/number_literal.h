#pragma once

#include <string>

#include "../span.h"
#include "token.h"

class Number_literal : public Token {
    public:
        Number_literal(std::string value, int base, Span span) : 
        m_value(value), m_base(base),  m_span(span) {}

        std::string asString() override { return m_value; }
    private:
        std::string m_value;
        int m_base;
        Span m_span;
};