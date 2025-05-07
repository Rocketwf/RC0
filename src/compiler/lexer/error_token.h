#pragma once

#include <string>

#include "token.h"
#include "../span.h"

class ErrorToken: public Token { //TODO: Fix name
    public:
    ErrorToken(std::string value, Span span):
        m_value(value),
        m_span(span) {}

    std::string asString() override {return m_value;}
    private:
    std::string m_value;
    Span m_span;
};