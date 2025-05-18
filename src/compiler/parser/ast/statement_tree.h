#pragma once

#include <vector>
#include <optional>

#include "expression_tree.h"
#include "type_tree.h"
#include "../visitor/visitor.h"
#include "../../lexer/operator.h"
#include "l_value_tree.h"


//class ExpressionTree;

class StatementTree: public Tree {};

class AssignmentTree : public StatementTree {
    public:
     AssignmentTree(std::unique_ptr<LValueTree> l_value_tree,
                    std::unique_ptr<Operator> op,
                    std::unique_ptr<ExpressionTree> expression_tree)
         : _l_value_tree(std::move(l_value_tree)),
           _op(std::move(op)),
           _expression_tree(std::move(expression_tree)) {};
     Span span() const override;
     void accept(Visitor& visitor, Context& context) override;

     const std::unique_ptr<LValueTree> _l_value_tree;
     const std::unique_ptr<Operator> _op;
     const std::unique_ptr<ExpressionTree> _expression_tree;
};


class BlockTree : public StatementTree {
    public:
    BlockTree(std::vector<std::unique_ptr<StatementTree>> statement_trees, Span span):
        _statement_trees(std::move(statement_trees)),
        m_span(std::move(span)) {};
    Span span() const override;
    void accept(Visitor& visitor, Context& context) override;
    //std::vector<std::unique_ptr<StatementTree>> statement_trees() {
    //  return m_statement_trees;
    //}

    std::vector<std::unique_ptr<StatementTree>> _statement_trees;
    private:
     const Span m_span;
};


class DeclarationTree : public StatementTree {
    public:
     DeclarationTree(std::unique_ptr<TypeTree> type_tree,
                     std::unique_ptr<NameTree> name_tree,
                     std::unique_ptr<ExpressionTree> initializer)
         : _type_tree(std::move(type_tree)),
           _name_tree(std::move(name_tree)),
           _initializer(std::move(initializer)) {};
     Span span() const override;
     void accept(Visitor& visitor, Context& context) override;

     const std::unique_ptr<TypeTree> _type_tree;
     const std::unique_ptr<NameTree> _name_tree;
     const std::unique_ptr<ExpressionTree> _initializer;
};


class ReturnTree : public StatementTree {
    public:
     ReturnTree(std::unique_ptr<ExpressionTree> expression, Position start)
         : _expression(std::move(expression)), m_start(start) {}
     Span span() const override;
     void accept(Visitor& visitor, Context& context) override;

     const std::unique_ptr<ExpressionTree> _expression;
     private:
     const Position m_start;
};