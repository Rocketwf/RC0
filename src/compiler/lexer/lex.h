#pragma once

#include <string>
#include <optional>
#include <memory>


#include "keyword.h"
#include "separator.h"
#include "operator.h"
#include "../span.h" //TODO: Use absolute paths instead of relative
#include "error_token.h"

class Lexer {
    public:
    Lexer forString(std::string source);
    std::optional<Token> nextToken();

    private:
    const std::string m_source;
    int m_pos;
    int m_linestart;
    int m_line;

    Lexer(const std::string& source):
        m_source(source) {};

    std::optional<ErrorToken> skip_whitespace();
    Separator separator(Separator::Separator_type par_open);
    std::unique_ptr<Token> lex_identifier_or_keyword();
    std::unique_ptr<Token> lex_number();
    bool is_hex_prefix();
    bool is_identifier_char(char c);
    bool is_numeric(char c);
    bool is_hex(char c);
    std::unique_ptr<Token> single_or_assign_operator(
        Operator::Operator_type single, Operator::Operator_type assign);
    Span build_span(int proceed);
    char peek();
    char peek(int offset);
    bool has_more(int offset);

};