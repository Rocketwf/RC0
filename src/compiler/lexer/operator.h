#pragma once

#include <string>
#include <unordered_map>

#include "token.h"
#include "../span.h"

class Operator: public Token {
    public:

    enum class Operator_type {
        PLUS,
        MINUS
    };

    Operator(Operator_type type, Span span):
        m_type(type),
        m_span(span) {}
        
    std::unordered_map<Operator_type, std::string> operators = {
        {Operator_type::PLUS, "+"},
        {Operator_type::MINUS, "-"}
    };
    std::string asString() {
        return operators[m_type];
    }
    private:
    Operator_type m_type;
    Span m_span;
};