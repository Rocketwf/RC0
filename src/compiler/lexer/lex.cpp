#include "lex.h"
#include "identifier.h"
#include "number_literal.h"

#include <optional>

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
                    continue;
                }
                return std::nullopt;
            }
            break;
        }
        }
    }
    if (!has_more(0) && currentCommentType == CommentType::MULTILINE) {
        return std::optional<ErrorToken>{ErrorToken(m_source.substr(comment_start), build_span(0))};
    }
    return std::nullopt;
}

Separator Lexer::separator(Separator::Separator_type par_open) {
    return Separator(par_open, build_span(1));
}

constexpr inline auto enum_range = [](auto front, auto back) {
  return std::views::iota(std::to_underlying(front),
                          std::to_underlying(back) + 1) |
         std::views::transform([](auto e) { return decltype(front)(e); });
};

std::unique_ptr<Token> Lexer::lex_identifier_or_keyword() {
    int off = 1;
    while (has_more(off) && is_identifier_char(peek(off))) {
        off++;
    }
    std::string id = m_source.substr(m_pos, m_pos + off);
    for (const auto& it: Keyword::keywords) {
        if (it.second == id) {
            return std::make_unique<Token>(Keyword(it.first, build_span(off)));
        }
    }
    return std::make_unique<Token>(Identifier(id, build_span(off)));
}

std::unique_ptr<Token> Lexer::lex_number() {
    if (is_hex_prefix()) {
        int off = 2;
        while (has_more(off) && is_hex(peek(off))) {
            off++;
        }
        if (off == 2) {
            return std::make_unique<Token>(ErrorToken(m_source.substr(m_pos, m_pos + off), build_span(2)));
        }
        return std::make_unique<Token>(Number_literal(m_source.substr(m_pos, m_pos + off), 16, build_span(off)));
    }
    int off = 1;
    while (has_more(off) && is_numeric(peek(off))) {
        off++;
    }
    if (peek() == '0' && off > 1) {
        //no leading zeroes
        return std::make_unique<Token>(ErrorToken(m_source.substr(m_pos, m_pos + off), build_span(off)));
    }
    return std::make_unique<Token>(Number_literal(m_source.substr(m_pos, m_pos + off), 10, build_span(off)));
}

bool Lexer::is_hex_prefix() { 
    return peek() == '0' && has_more(1) && (peek(1) == 'x' || peek(1) == 'X');
}

bool Lexer::is_identifier_char(char c) {
    return c == '_' 
        || c >= 'a' && c <= 'z' 
        || c >= 'A' && c <= 'Z' 
        || c >= '0' && c <= '9';
}

bool Lexer::is_numeric(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::is_hex(char c) {
    return is_numeric(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

std::unique_ptr<Token> Lexer::single_or_assign_operator(
    Operator::Operator_type single, Operator::Operator_type assign) {
  if (has_more(1) && peek(1) == '=') {
    return std::make_unique<Token>(Operator(assign, build_span(2)));
  }
  return std::make_unique<Token>(Operator(single, build_span(2)));
}

Span Lexer::build_span(int proceed) { 
    int start = m_pos;
    m_pos += proceed;
    return Span(m_line, start - m_line, m_line, start - m_line + proceed) ;
}

char Lexer::peek() { 
    return m_source.at(m_pos);
}

char Lexer::peek(int offset) { 
    return m_source.at(m_pos); 
}

bool Lexer::has_more(int offset) { 
    return m_pos + offset < m_source.length(); 
}
