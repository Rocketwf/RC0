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
         : m_l_value_tree(std::move(l_value_tree)),
           m_op(std::move(op)),
           m_expression_tree(std::move(expression_tree)) {};
     Span span() const override;
     void accept(Visitor& visitor, Context& context) override;

    private:
     const std::unique_ptr<LValueTree> m_l_value_tree;
     const std::unique_ptr<Operator> m_op;
     const std::unique_ptr<ExpressionTree> m_expression_tree;
};


class BlockTree : public StatementTree {
    public:
    BlockTree(std::vector<std::unique_ptr<StatementTree>> statement_trees, Span span):
        m_statement_trees(std::move(statement_trees)),
        m_span(std::move(span)) {};
    Span span() const override;
    void accept(Visitor& visitor, Context& context) override;
    //std::vector<std::unique_ptr<StatementTree>> statement_trees() {
    //  return m_statement_trees;
    //}

    private:
     std::vector<std::unique_ptr<StatementTree>> m_statement_trees;
     const Span m_span;
};


class DeclarationTree : public StatementTree {
    public:
     DeclarationTree(std::unique_ptr<TypeTree> type_tree,
                     std::unique_ptr<NameTree> name_tree,
                     std::unique_ptr<ExpressionTree> initializer)
         : m_type_tree(std::move(type_tree)),
           m_name_tree(std::move(name_tree)),
           m_initializer(std::move(initializer)) {};
     Span span() const override;
     void accept(Visitor& visitor, Context& context) override;

    private:
     const std::unique_ptr<TypeTree> m_type_tree;
     const std::unique_ptr<NameTree> m_name_tree;
     const std::unique_ptr<ExpressionTree> m_initializer;
};


class ReturnTree : public StatementTree {
    public:
     ReturnTree(std::unique_ptr<ExpressionTree> expression, Position start)
         : m_expression(std::move(expression)), m_start(start) {}
     Span span() const override;
     void accept(Visitor& visitor, Context& context) override;

    private:
     const std::unique_ptr<ExpressionTree> m_expression;
     const Position m_start;
};