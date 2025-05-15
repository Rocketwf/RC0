#pragma once

#include <string>

#include "token_type.h"
#include "keyword_type.h"
#include "separator_type.h"
#include "operator_type.h"
#include "compiler/span.h"

class Token {
    public:
        Token(Span span):
            m_span(span) {};
        virtual ~Token() = default;

        virtual bool is_keyword(KeywordType keyword_type) const {
            return false;
        }
        virtual bool is_operator(OperatorType operator_type) const {
            return false;
        }
        virtual bool is_separator(SeparatorType separator_type) const {
            return false;
        }
        virtual std::string as_string() const = 0;

        Span span() const {
            return m_span;
        };

        virtual TokenType token_type() = 0; //TODO: Make const
    protected:
    Span m_span;
};