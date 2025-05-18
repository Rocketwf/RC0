#pragma once

#include <functional>
#include <iterator>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "compiler/lexer/lex.h"
#include "compiler/lexer/keyword.h"
#include "compiler/lexer/operator.h"
#include "compiler/lexer/separator.h"
#include "compiler/lexer/identifier.h"

#include "compiler/parser/parse_exception.h"

class Token;

class TokenSource {
 private:
  std::vector<std::unique_ptr<Token>> m_tokens;
  size_t m_idx = 0;

  void expect_has_more() const {
    if (m_idx >= m_tokens.size()) {
      throw ParseException("reached end of file");
    }
  }

 public:
  explicit TokenSource(Lexer& lexer) {
    while(auto opt = lexer.next_token()) {
      m_tokens.emplace_back(std::move(*opt));
    }
  }

  Token& peek() {
    expect_has_more();
    return *m_tokens[m_idx];
  }

  Keyword expect_keyword(KeywordType type);
  Separator expect_separator(SeparatorType type);
  Operator expect_operator(OperatorType type);
  Identifier expect_identifier();

  Token& consume() {
    expect_has_more();
    return *m_tokens[m_idx++];
  }

  bool has_more() const { return m_idx < m_tokens.size(); }
};

//TODO: Put these in .cpp
Keyword TokenSource::expect_keyword(KeywordType type) {
  auto& token = peek();
  if (auto* keyword = dynamic_cast<Keyword*>(&token)) {
    if (keyword->get_type() == type) {
      consume();
      return *keyword;
    }
  }
  throw ParseException("Expected keyword but got " + token.as_string());
}

Separator TokenSource::expect_separator(SeparatorType type) {
  auto& token = peek();
  if (auto* sep = dynamic_cast<Separator*>(&token)) {
    if (sep->get_type() == type) {
      consume();
      return *sep;
    }
  }
  throw ParseException("Expected separator but got " + token.as_string());
}

Operator TokenSource::expect_operator(OperatorType type) {
    auto& token = peek();
    if (auto* op = dynamic_cast<Operator*>(&token)) {
      if (op->get_type() == type) {
        consume();
        return *op;
      }
    }
    throw ParseException("Expected operator but got " + token.as_string());
}

Identifier TokenSource::expect_identifier() {
  auto& token = peek();
  if (auto* id = dynamic_cast<Identifier*>(&token)) {
    consume();
    return *id;
  }
  throw ParseException("Expected identifier but got " + token.as_string());
}