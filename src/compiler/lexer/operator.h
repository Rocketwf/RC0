#pragma once

#include <string>
#include <unordered_map>

#include "token.h"
#include "../span.h"
#include "operator_type.h"

class Operator: public Token {
    public:

    bool is_operator(OperatorType operator_type) const override {
        return get_type() == operator_type;
    }

    Operator(OperatorType type, Span span):
        Token(span), 
        m_type(type) {}

    std::unordered_map<OperatorType, std::string> operators = {
        {OperatorType::ASSIGN_MINUS, "-="},
        {OperatorType::MINUS, "-"},
        {OperatorType::ASSIGN_PLUS, "+="},
        {OperatorType::PLUS, "+"},
        {OperatorType::MUL, "*"},
        {OperatorType::ASSIGN_MUL, "*="},
        {OperatorType::ASSIGN_DIV, "/="},
        {OperatorType::DIV, "/"},
        {OperatorType::ASSIGN_MOD, "%="},
        {OperatorType::MOD, "%"},
        {OperatorType::ASSIGN, "="}};
        
    std::string as_string() const override {
        return operators.at(m_type);
    }
    OperatorType get_type() const { return m_type; }
    TokenType token_type() override { return TokenType::OPERATOR; };

    private:
    OperatorType m_type;
};