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
    static Lexer for_string(std::string source);
    std::optional<std::unique_ptr<Token>> next_token();

    private:
    const std::string m_source;
    int m_pos = 0;
    int m_linestart = 0;
    int m_line = 0;

    Lexer(const std::string& source):
        m_source(source) {};

    std::optional<ErrorToken> skip_whitespace();
    std::unique_ptr<Token> separator(SeparatorType par_open);
    std::unique_ptr<Token> lex_identifier_or_keyword();
    std::unique_ptr<Token> lex_number();
    bool is_hex_prefix();
    bool is_identifier_char(char c);
    bool is_numeric(char c);
    bool is_hex(char c);
    std::unique_ptr<Token> single_or_assign_operator(
        OperatorType single, OperatorType assign);
    Span build_span(int proceed);
    char peek();
    char peek(int offset);
    bool has_more(int offset);

};