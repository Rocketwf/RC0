#include "no_op_visitor.h"

#include "compiler/parser/ast/expression_tree.h"
#include "compiler/parser/ast/function_tree.h"
#include "compiler/parser/ast/l_value_tree.h"
#include "compiler/parser/ast/name_tree.h"
#include "compiler/parser/ast/program_tree.h"
#include "compiler/parser/ast/statement_tree.h"
#include "compiler/parser/ast/type_tree.h"

void NoOpVisitor::visit(AssignmentTree& assignment_tree,
                        Context& context) {
    return;
}
void NoOpVisitor::visit(BinaryOperationTree& binary_operation_tree, 
                        Context& context) {
    return;
}
void NoOpVisitor::visit(BlockTree& block_tree, 
                        Context& context) {
    return;
}
void NoOpVisitor::visit(DeclarationTree& declaration_tree,
                        Context& context) {
    return;
}
void NoOpVisitor::visit(FunctionTree& function_tree,
                        Context& context) {
    return;
}
void NoOpVisitor::visit(IdentExpressionTree& ident_expression_tree, 
                        Context& context) {
    return;
}
void NoOpVisitor::visit(LiteralTree& literal_tree,
                        Context& context) {
    return;
}
void NoOpVisitor::visit(LValueIdentTree& lvalue_ident_tree,
                        Context& context) {
    return;
}
void NoOpVisitor::visit(NameTree& name_tree, 
                        Context& context) {
    return;
}
void NoOpVisitor::visit(NegateTree& negate_tree,
                        Context& context) {
    return;
}
void NoOpVisitor::visit(ProgramTree& program_tree,
                        Context& context) {
    return;
}
void NoOpVisitor::visit(ReturnTree& return_tree,
                        Context& context) {
    return;
}
void NoOpVisitor::visit(TypeTree& type_tree, 
                        Context& context) {
    return;
}