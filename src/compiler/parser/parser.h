#pragma once

#include "token_source.h"
#include "compiler/parser/ast/tree.h"
#include "compiler/parser/ast/expression_tree.h"
#include "compiler/parser/ast/function_tree.h"
#include "compiler/parser/ast/l_value_tree.h"
#include "compiler/parser/ast/name_tree.h"
#include "compiler/parser/ast/program_tree.h"
#include "compiler/parser/ast/statement_tree.h"
#include "compiler/parser/ast/type_tree.h"
#include "compiler/lexer/number_literal.h"

class Parser {
 private:
  TokenSource m_token_source;

  std::unique_ptr<NameTree> name(const Identifier& ident) {
    return std::make_unique<NameTree>(Name::for_identifier(ident),
                                      ident.span());
  }

  std::unique_ptr<FunctionTree> parse_function() {
    auto return_type = m_token_source.expect_keyword(KeywordType::INT);
    auto identifier = m_token_source.expect_identifier();
    m_token_source.expect_separator(SeparatorType::PAR_OPEN);
    //Parameters here
    m_token_source.expect_separator(SeparatorType::PAR_CLOSE);
    auto body = parse_block();

    return std::make_unique<FunctionTree>(
        std::make_unique<TypeTree>(std::make_unique<BasicType>(BasicTypeEnum::INT),
                                   return_type.span()), 
                                   name(identifier), 
                                   std::move(body));
  }

  std::unique_ptr<BlockTree> parse_block() {
    auto body_open = m_token_source.expect_separator(SeparatorType::BRACE_OPEN);
    std::vector<std::unique_ptr<StatementTree>> statements;
    Token* next_token = &m_token_source.peek();
    while (next_token->token_type() != TokenType::SEPARATOR 
          || dynamic_cast<Separator*>(next_token)->get_type() != SeparatorType::BRACE_CLOSE) {
      statements.push_back(parse_statement());
      next_token = &m_token_source.peek();
    }

    auto body_close = m_token_source.expect_separator(SeparatorType::BRACE_CLOSE);
    return std::make_unique<BlockTree>(
        std::move(statements), body_open.span().merge(body_close.span()));
  }

  std::unique_ptr<StatementTree> parse_statement() {
    std::unique_ptr<StatementTree> statement;
    if (m_token_source.peek().is_keyword(KeywordType::INT)) {
      statement = parse_declaration();
    } else if (m_token_source.peek().is_keyword(KeywordType::RETURN)) {
      statement = parse_return();
    } else {
      statement = parse_simple();
    }
    m_token_source.expect_separator(SeparatorType::SEMICOLON);
    return statement;
  }

  std::unique_ptr<StatementTree> parse_declaration() {
    auto type = m_token_source.expect_keyword(KeywordType::INT);
    auto ident = m_token_source.expect_identifier();
    std::unique_ptr<ExpressionTree> expr = nullptr;
    if (m_token_source.peek().is_operator(OperatorType::ASSIGN)) {
      m_token_source.expect_operator(OperatorType::ASSIGN);
      expr = parse_expression();
    }

    return std::make_unique<DeclarationTree>(
        std::make_unique<TypeTree>(std::make_unique<BasicType>(BasicTypeEnum::INT), type.span()), 
        name(ident), 
        std::move(expr));
  }

  std::unique_ptr<StatementTree> parse_simple() {
    auto l_value = parse_l_value();
    auto assignment_operator = parse_assignment_operator();
    auto expression = parse_expression();

    return std::make_unique<AssignmentTree>(std::move(l_value), std::move(assignment_operator), std::move(expression));
  }

  std::unique_ptr<Operator> parse_assignment_operator() {
    if (auto op = dynamic_cast<Operator*>(&m_token_source.peek())) {
      switch (op->get_type()) {
        case OperatorType::ASSIGN:
        case OperatorType::ASSIGN_DIV:
        case OperatorType::ASSIGN_MINUS:
        case OperatorType::ASSIGN_MOD:
        case OperatorType::ASSIGN_MUL:
        case OperatorType::ASSIGN_PLUS:
          m_token_source.consume();
          return std::unique_ptr<Operator>(op);
        default:
          throw ParseException("expected assignment but got " +
                               op->as_string());
      }
    }
    throw ParseException(
        "expected assignment but got " +
        m_token_source.peek().as_string());
  }

  std::unique_ptr<LValueTree> parse_l_value() {
    if (m_token_source.peek().is_separator(SeparatorType::PAR_OPEN)) {
      m_token_source.expect_separator(SeparatorType::PAR_OPEN);
      auto inner = parse_l_value();
      m_token_source.expect_separator(SeparatorType::PAR_CLOSE);
      return inner;
    }
    auto identifier = m_token_source.expect_identifier();
    return std::make_unique<LValueIdentTree>(name(identifier));
  }

  std::unique_ptr<StatementTree> parse_return() {
    auto ret = m_token_source.expect_keyword(KeywordType::RETURN);
    auto expression = parse_expression();
    return std::make_unique<ReturnTree>(std::move(expression), ret.span().start());
  }

  std::unique_ptr<ExpressionTree> parse_expression() {
    auto lhs = parse_term();
    while (true) {
      if (auto op = dynamic_cast<Operator*>(&m_token_source.peek())) {
        if (op->get_type() == OperatorType::PLUS ||
            op->get_type() == OperatorType::MINUS) {
          m_token_source.consume();
          lhs = std::make_unique<BinaryOperationTree>(std::move(lhs), parse_term(),
                                                      op->get_type());
        } else {
          return lhs;
        }
      } else {
        return lhs;
      }
    }
  }

  std::unique_ptr<ExpressionTree> parse_term() {
    auto lhs = parse_factor();
    while (true) {
      if (auto op = dynamic_cast<Operator*>(&m_token_source.peek())) {
        if (op->get_type() == OperatorType::MUL ||
            op->get_type() == OperatorType::DIV ||
            op->get_type() == OperatorType::MOD) {
          m_token_source.consume();
          lhs = std::make_unique<BinaryOperationTree>(std::move(lhs), parse_factor(),
                                                      op->get_type());
        } else {
          return lhs;
        }
      } else {
        return lhs;
      }
    }
  }

  std::unique_ptr<ExpressionTree> parse_factor() {
    auto& next_token = m_token_source.peek();
    switch (next_token.token_type()) {
      case TokenType::SEPARATOR: {
        if(next_token.is_separator(SeparatorType::PAR_OPEN)) {
          m_token_source.consume();
          auto expr = parse_expression();
          m_token_source.expect_separator(SeparatorType::PAR_CLOSE);
          return expr;
        }
      }
      case TokenType::OPERATOR: {
        if (next_token.is_operator(OperatorType::MINUS)) {
          auto span = m_token_source.consume().span();
          return std::make_unique<NegateTree>(parse_factor(), span);
        }
      }
      case TokenType::IDENTIFIER: {
        auto& ident_token = m_token_source.consume();
        return std::make_unique<IdentExpressionTree>(
            name(dynamic_cast<Identifier&>(ident_token)));
      }
      case TokenType::NUMBER: {
        auto lit = dynamic_cast<NumberLiteral*>(&m_token_source.consume());
        return std::make_unique<LiteralTree>(lit->as_string(), lit->base(),
                                             lit->span());
      }
      default:
        throw ParseException(
            "invalid factor " +
            m_token_source.peek().as_string());
    }
  }

 public:
  explicit Parser(TokenSource& source) : m_token_source(std::move(source)) {}

  std::unique_ptr<ProgramTree> parse_program() {
    std::vector<std::unique_ptr<FunctionTree>> functions;
    functions.push_back(parse_function());
    auto programTree = std::make_unique<ProgramTree>(std::move(functions));
    if (m_token_source.has_more()) {
      throw ParseException(
          "expected end of input but got " +
          m_token_source.peek().as_string());
    }
    return programTree;
  }
};
