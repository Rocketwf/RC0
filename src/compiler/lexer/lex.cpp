#include "lex.h"

#include "identifier.h"
#include "number_literal.h"

#include <optional>
#include <ranges>
#include <utility>
#include <iostream>

Lexer Lexer::for_string(std::string source) { 
    return Lexer(source); 
}

std::optional<std::unique_ptr<Token>> Lexer::next_token() {
    if (auto error = skip_whitespace()) {
        return std::make_unique<ErrorToken>(std::move(*error));
    }
    if (!has_more(0)) {
      return std::nullopt;
    }
    char c = peek();
    std::unique_ptr<Token> t;
    switch (c) {
        case '(': t = separator(SeparatorType::PAR_OPEN); break;
        case ')': t = separator(SeparatorType::PAR_CLOSE); break;
        case '{': t = separator(SeparatorType::BRACE_OPEN); break;
        case '}': t = separator(SeparatorType::BRACE_CLOSE); break;
        case ';': t = separator(SeparatorType::SEMICOLON); break;
        case '-': t = single_or_assign_operator(OperatorType::MINUS, OperatorType::ASSIGN_MINUS); break;
        case '+': t = single_or_assign_operator(OperatorType::PLUS, OperatorType::ASSIGN_PLUS); break;
        case '*': t = single_or_assign_operator(OperatorType::MUL, OperatorType::ASSIGN_MUL); break;
        case '/': t = single_or_assign_operator(OperatorType::DIV, OperatorType::ASSIGN_DIV); break;
        case '%': t = single_or_assign_operator(OperatorType::MOD, OperatorType::ASSIGN_MOD); break;
        case '=': t = std::make_unique<Operator>(OperatorType::ASSIGN, build_span(1)); break;
        default:
            if (is_identifier_char(c)) {
                if (is_numeric(c)) {
                    t = lex_number();
                } else {
                    t = lex_identifier_or_keyword();
                }
            } else {
                t = std::make_unique<ErrorToken>(std::string(1, c), build_span(1));
            }
    }
    return t;
}

std::optional<ErrorToken> Lexer::skip_whitespace() {
    enum CommentType {
        NO_COMMENT,
        SINGLE_LINE,
        MULTILINE
    };
    CommentType currentCommentType = NO_COMMENT;
    int multi_line_comment_depth = 0;
    int comment_start = -1;
    while(has_more(0)) {
        switch (peek()) {
          case ' ':
          case '\t':
            m_pos++;
            break;
          case '\n':
          case '\r': {
            m_pos++;
            m_linestart = m_pos;
            m_line++;
            if (currentCommentType == CommentType::SINGLE_LINE) {
                currentCommentType = CommentType::NO_COMMENT;
            }
            break;
        }
        case '/': {
            if (currentCommentType == CommentType::SINGLE_LINE) {
                m_pos++;
                continue;
            }
            if (has_more(1)) {
                if (peek(1) == '/' && currentCommentType == CommentType::NO_COMMENT) {
                    currentCommentType = CommentType::SINGLE_LINE;
                } else if (peek(1) ==  '*') {
                    currentCommentType = CommentType::MULTILINE;
                    multi_line_comment_depth++;
                } else if (currentCommentType == CommentType::MULTILINE) {
                    m_pos++;
                    continue;
                } else {
                    return std::nullopt;
                }
                comment_start = m_pos;
                m_pos += 2;
                continue;
            }
            if (multi_line_comment_depth > 0) {
                m_pos++;
                continue;
            }
            return std::nullopt;
        }
        default: {
            if (currentCommentType == CommentType::MULTILINE) {
                if (peek() == '*' && has_more(1) && peek(1) == '/') { //in case there are nexted "/**/"
                    m_pos += 2;
                    multi_line_comment_depth--;
                    currentCommentType = multi_line_comment_depth == 0 ? CommentType::NO_COMMENT : CommentType::MULTILINE;
                } else {
                    m_pos++;
                }
                continue;
            } else if (currentCommentType == CommentType::SINGLE_LINE) {
                m_pos++;
                continue;
            }
            return std::nullopt;
        }
        }
    }
    if (!has_more(0) && currentCommentType == CommentType::MULTILINE) {
      return std::optional<ErrorToken>{
          ErrorToken(m_source.substr(comment_start, 0), build_span(0))};
    }
    return std::nullopt;
}

std::unique_ptr<Token> Lexer::separator(SeparatorType par_open) {
    return std::make_unique<Separator>(par_open, build_span(1));
}

std::unique_ptr<Token> Lexer::lex_identifier_or_keyword() {
    int off = 1;
    while (has_more(off) && is_identifier_char(peek(off))) {
        off++;
    }
    std::string id = m_source.substr(m_pos, off);
    for (const auto& it : Keyword::keywords) {
      if (it.second == id) {
        return std::make_unique<Keyword>(it.first, build_span(off));
      }
    }
    return std::make_unique<Identifier>(id, build_span(off));
}

std::unique_ptr<Token> Lexer::lex_number() {
    if (is_hex_prefix()) {
        int off = 2;
        while (has_more(off) && is_hex(peek(off))) {
            off++;
        }
        auto val = m_source.substr(m_pos, off);
        if (off == 2) {
            return std::make_unique<ErrorToken>(val, build_span(2));
        }
        auto t = std::make_unique<NumberLiteral>(val, 16, build_span(off));
        return t; 
    }
    int off = 1;
    while (has_more(off) && is_numeric(peek(off))) {
        off++;
    }
    auto val = m_source.substr(m_pos, off);
    if (peek() == '0' && off > 1) {
        //no leading zeroes
        return std::make_unique<ErrorToken>(val, build_span(off));
    }
    return std::make_unique<NumberLiteral>(val , 10, build_span(off));
}

bool Lexer::is_hex_prefix() { 
    return peek() == '0' && has_more(1) && (peek(1) == 'x' || peek(1) == 'X');
}

bool Lexer::is_identifier_char(char c) {
    return c == '_' 
        || (c >= 'a' && c <= 'z') 
        || (c >= 'A' && c <= 'Z') 
        || (c >= '0' && c <= '9');
}

bool Lexer::is_numeric(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::is_hex(char c) {
    return is_numeric(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

std::unique_ptr<Token> Lexer::single_or_assign_operator(
    OperatorType single, OperatorType assign) {
  if (has_more(1) && peek(1) == '=') {
    return std::make_unique<Operator>(assign, build_span(2));
  }
  return std::make_unique<Operator>(single, build_span(1));
}

Span Lexer::build_span(int proceed) { 
    int start = m_pos;
    m_pos += proceed;
    Position s(m_line, start - m_line);
    Position e(m_line, m_pos - m_linestart);
    return Span(s, e) ;
}

char Lexer::peek() {
  return peek(0);
}

char Lexer::peek(int offset) { return m_source.at(m_pos + offset); }

bool Lexer::has_more(int offset) { 
    return (size_t)(m_pos + offset) < m_source.length(); 
}
