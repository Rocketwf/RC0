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
         : _lhs(std::move(lhs)),
           _rhs(std::move(rhs)),
           m_operator_type(operator_type) {};
     Span span() const override;
     void accept(Visitor& visitor, Context& context) override;

     const std::unique_ptr<ExpressionTree> _lhs;
     const std::unique_ptr<ExpressionTree> _rhs;
     const OperatorType m_operator_type;
};


class IdentExpressionTree : public ExpressionTree {
    public:
     IdentExpressionTree(std::unique_ptr<NameTree> name)
         : _name(std::move(name)) {};
     Span span() const override;
     void accept(Visitor& visitor, Context& context) override;

     const std::unique_ptr<NameTree> _name;
};


class LiteralTree : public ExpressionTree {
    public:
    LiteralTree(std::string value, int base, Span span):
        _value(value), _base(base), _span(span) {};
    std::optional<long> parse_value();
    
    Span span() const override;
    void accept(Visitor& visitor, Context& context) override;

    const std::string _value;
    const int _base;
    const Span _span;
    
    private:
    std::optional<long> parse_dec(int end) const;
    std::optional<long> parse_hex(int end) const;
};


class NegateTree : public ExpressionTree {
    public:
      NegateTree(std::unique_ptr<ExpressionTree> expression, Span minus_pos)
         : _expression(std::move(expression)), _minus_pos(minus_pos) {};
      void accept(Visitor& visitor, Context& context) override;
      Span span() const override;

      const std::unique_ptr<ExpressionTree> _expression;
      const Span _minus_pos;
};
