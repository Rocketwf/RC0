#pragma once 

#include <string>

#include "token.h"
#include "../span.h"

class Identifier: public Token {
    public:
        Identifier(std::string value, Span span): 
            Token(span), m_value(value) {}

        std::string as_string() const override { return m_value; }

        TokenType token_type() override { return TokenType::IDENTIFIER;};
    private:
        std::string m_value;
};