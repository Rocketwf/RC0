#pragma once

#include <string>

#include "../span.h"
#include "token.h"
#include <iostream>
class NumberLiteral : public Token {
    public:
        NumberLiteral(std::string value, int base, Span span) : 
        Token(span), m_value(value), m_base(base) {}

        std::string as_string() const override {
          return m_value;
        }
        int base() const { return m_base; }
        TokenType token_type() override { return TokenType::NUMBER; }
    private:
        std::string m_value;
        int m_base;
};