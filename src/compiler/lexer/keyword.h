#pragma once
#include <unordered_map>
#include <string>

#include "token.h"
#include "../span.h"

class Keyword: public Token {
    public:
        enum class Keyword_type {
            STRUCT
        };

        Keyword(Keyword_type type, Span span):
            m_type(type),
            m_span(span) {}

        inline static std::unordered_map<Keyword_type, std::string> keywords = {
            {Keyword_type::STRUCT, "struct"}
        };

        std::string asString() {
            return keywords[m_type];
        }

    private:
        Keyword_type m_type;
        Span m_span;
};