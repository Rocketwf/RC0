#pragma once

#include <memory>

class Context;
class Tree;
class AssignmentTree;
class BinaryOperationTree;
class BlockTree;
class DeclarationTree;
class FunctionTree;
class IdentExpressionTree;
class LiteralTree;
class LValueIdentTree;
class NameTree;
class NegateTree;
class ProgramTree;
class ReturnTree;
class TypeTree;


class Visitor {
    public:
    virtual ~Visitor() = default;

    virtual void visit(AssignmentTree& assignment_tree, Context& data) = 0;

    virtual void visit(BinaryOperationTree& binary_operation_tree , Context& data) = 0;

    virtual void visit(BlockTree& block_tree, Context& data) = 0;

    virtual void visit(DeclarationTree& declaration_tree, Context& data) = 0;

    virtual void visit(FunctionTree& function_tree, Context& data) = 0;

    virtual void visit(IdentExpressionTree& ident_expression_tree, Context& data) = 0;

    virtual void visit(LiteralTree& literal_tree, Context& data) = 0;

    virtual void visit(LValueIdentTree& lvalue_ident_tree, Context& data) = 0;

    virtual void visit(NameTree& name_tree, Context& data) = 0;

    virtual void visit(NegateTree& negate_tree, Context& data) = 0;

    virtual void visit(ProgramTree& program_tree, Context& data) = 0;

    virtual void visit(ReturnTree& return_tree, Context& data) = 0;

    virtual void visit(TypeTree& type_tree, Context& data) = 0;
};