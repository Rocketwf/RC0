#include "recursive_postorder_visitor.h"

#include "compiler/parser/ast/expression_tree.h"
#include "compiler/parser/ast/function_tree.h"
#include "compiler/parser/ast/l_value_tree.h"
#include "compiler/parser/ast/name_tree.h"
#include "compiler/parser/ast/program_tree.h"
#include "compiler/parser/ast/statement_tree.h"
#include "compiler/parser/ast/type_tree.h"

void RecursivePostOrderVisitor::visit(AssignmentTree& assignment_tree,
                                      Context& context) {
  assignment_tree._l_value_tree->accept(*this, context);
  assignment_tree._expression_tree->accept(*this, context);
  m_visitor.visit(assignment_tree, context);
}

void RecursivePostOrderVisitor::visit(
    BinaryOperationTree& binary_operation_tree, Context& context) {
  binary_operation_tree._lhs->accept(*this, context);
  binary_operation_tree._rhs->accept(*this, context);
  m_visitor.visit(binary_operation_tree, context);
}

void RecursivePostOrderVisitor::visit(BlockTree& block_tree, Context& context) {
  for (auto& statement : block_tree._statement_trees) {
    statement->accept(*this, context);
  }
  m_visitor.visit(block_tree, context);
}

void RecursivePostOrderVisitor::visit(DeclarationTree& declaration_tree,
                                      Context& context) {
  declaration_tree._type_tree->accept(*this, context);
  declaration_tree._name_tree->accept(*this, context);
  if (declaration_tree._initializer) { //?? is this right
    declaration_tree._initializer->accept(*this, context);
  }
  m_visitor.visit(declaration_tree, context);
}

void RecursivePostOrderVisitor::visit(FunctionTree& function_tree,
                                      Context& context) {
  function_tree._return_type->accept(*this, context);
  function_tree._name->accept(*this, context);
  function_tree._body->accept(*this, context);
  m_visitor.visit(function_tree, context);
}

void RecursivePostOrderVisitor::visit(
    IdentExpressionTree& ident_expression_tree, Context& context) {
  ident_expression_tree._name->accept(*this, context);
  m_visitor.visit(ident_expression_tree, context);
}

void RecursivePostOrderVisitor::visit(LiteralTree& literal_tree,
                                      Context& context) {
  return m_visitor.visit(literal_tree, context);
}

void RecursivePostOrderVisitor::visit(LValueIdentTree& lvalue_ident_tree,
                                      Context& context) {
  lvalue_ident_tree._name->accept(*this, context);
  m_visitor.visit(lvalue_ident_tree, context);
}

void RecursivePostOrderVisitor::visit(NameTree& name_tree, Context& context) {
  m_visitor.visit(name_tree, context);
}

void RecursivePostOrderVisitor::visit(NegateTree& negate_tree,
                                      Context& context) {
  negate_tree._expression->accept(*this, context);
  m_visitor.visit(negate_tree, context);
}

void RecursivePostOrderVisitor::visit(ProgramTree& program_tree,
                                      Context& context) {
  for (auto& func : program_tree._top_level_trees) {
    func->accept(*this, context);
  }
  m_visitor.visit(program_tree, context);
}

void RecursivePostOrderVisitor::visit(ReturnTree& return_tree,
                                      Context& context) {
  return_tree._expression->accept(*this, context);
  m_visitor.visit(return_tree, context);
}

void RecursivePostOrderVisitor::visit(TypeTree& type_tree, Context& context) {
  return m_visitor.visit(type_tree, context);
}