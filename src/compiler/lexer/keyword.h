#pragma once

#include <unordered_map>
#include <string>

#include "token.h"
#include "../span.h"
#include "keyword_type.h"

class Keyword: public Token {
    public:

        bool is_keyword(KeywordType keyword_type) const override {
            return get_type() == keyword_type;
        }

        Keyword(KeywordType type, Span span):
            Token(span), m_type(type) {}

        inline static std::unordered_map<KeywordType, std::string> keywords = {
            {KeywordType::STRUCT, "struct"},
            {KeywordType::IF, "if"},
            {KeywordType::ELSE, "else"},
            {KeywordType::WHILE, "while"},
            {KeywordType::FOR, "for"},
            {KeywordType::CONTINUE, "continue"},
            {KeywordType::BREAK, "break"},
            {KeywordType::RETURN, "return"},
            {KeywordType::ASSERT, "assert"},
            {KeywordType::TRUE, "true"},
            {KeywordType::FALSE, "false"},
            {KeywordType::NULL_TYPE, "null"},
            {KeywordType::PRINT, "print"},
            {KeywordType::READ, "read"},
            {KeywordType::ALLOC, "alloc"},
            {KeywordType::ALLOC_ARRAY, "alloc_array"},
            {KeywordType::INT, "int"},
            {KeywordType::BOOL, "bool"},
            {KeywordType::VOID, "void"},
            {KeywordType::CHAR, "char"},
            {KeywordType::STRING, "string"}
        };

        std::string as_string() const override {
            return keywords[m_type];
        }

        KeywordType get_type() const {
            return m_type;
        }

        TokenType token_type() override { return TokenType::KEYWORD; }
    private:
        KeywordType m_type;
};