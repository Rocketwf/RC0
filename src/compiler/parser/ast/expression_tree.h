#pragma once

#include <optional>

#include "tree.h"
#include "name_tree.h"
#include "compiler/lexer/operator.h"

class ExpressionTree: public Tree {};

class BinaryOperationTree: public ExpressionTree {
    public:
     BinaryOperationTree(std::unique_ptr<ExpressionTree> lhs,
                         std::unique_ptr<ExpressionTree> rhs,
                         OperatorType operator_type)
         : m_lhs(std::move(lhs)),
           m_rhs(std::move(rhs)),
           m_operator_type(operator_type) {};
     Span span() const override;
     void accept(Visitor& visitor, Context& context) override;

    private:
    const std::unique_ptr<ExpressionTree> m_lhs;
    const std::unique_ptr<ExpressionTree> m_rhs;
    const OperatorType m_operator_type;
};


class IdentExpressionTree : public ExpressionTree {
    public:
     IdentExpressionTree(std::unique_ptr<NameTree> name)
         : m_name(std::move(name)) {};
     Span span() const override;
     void accept(Visitor& visitor, Context& context) override;

    private:
     const std::unique_ptr<NameTree> m_name;
};


class LiteralTree : public ExpressionTree {
    public:
    LiteralTree(std::string value, int base, Span span):
        m_value(value), m_base(base), m_span(span) {};
    std::optional<long> parse_value();
    
    Span span() const override;
    void accept(Visitor& visitor, Context& context) override;

    private:
    const std::string m_value;
    const int m_base;
    const Span m_span;

    std::optional<long> parse_dec(int end) const;
    std::optional<long> parse_hex(int end) const;
};


class NegateTree : public ExpressionTree {
    public:
      NegateTree(std::unique_ptr<ExpressionTree> expression, Span minus_pos)
         : m_expression(std::move(expression)), m_minus_pos(minus_pos) {};
      void accept(Visitor& visitor, Context& context) override;
      Span span() const override;
    private:
      const std::unique_ptr<ExpressionTree> m_expression;
      const Span m_minus_pos;
};
