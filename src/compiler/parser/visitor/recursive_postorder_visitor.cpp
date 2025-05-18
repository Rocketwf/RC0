/*
#include "recursive_postorder_visitor.h"


void RecursivePostOrderVisitor::visit(AssignmentTree& assignment_tree, Context&
context) { assignment_tree.l_value_tree().accept(*this, context);
  assignment_tree.expression_tree().accept(*this, accumulate(context));
  m_visitor.visit(assignment_tree, accumulate(context));
}


void RecursivePostOrderVisitor::visit(BinaryOperationTree&
binary_operation_tree, Context& context) { void r =
binary_operation_tree.lhs().accept(*this, context); r =
binary_operation_tree.rhs().accept(*this, accumulate(context, r)); r =
m_visitor.visit(binary_operation_tree, accumulate(context, r)); return r;
}


void RecursivePostOrderVisitor::visit(BlockTree& block_tree, Context& context) {
  for (auto& statement : block_tree.statement_trees()) {
    statement.accept(*this, context);
  }
  r = m_visitor.visit(block_tree, d);
  return r;
}


void RecursivePostOrderVisitor::visit(DeclarationTree& declaration_tree,
Context& context) { void r = declaration_tree.type().accept(*this, context); r =
declaration_tree.name().accept(*this, accumulate(context, r)); if
(declaration_tree.initializer()) { r =
declaration_tree.initializer().accept(*this, accumulate(context, r));
  }
  r = m_visitor.visit(declaration_tree, accumulate(context, r));
  return r;
}


void RecursivePostOrderVisitor::visit(FunctionTree& function_tree, Context&
context) { void r = function_tree.returnType().accept(*this, context); r =
function_tree.name().accept(*this, accumulate(context, r)); r =
function_tree.body().accept(*this, accumulate(context, r)); r =
m_visitor.visit(function_tree, accumulate(context, r)); return r;
}


void RecursivePostOrderVisitor::visit(IdentExpressionTree&
ident_expression_tree, Context& context) { void r =
ident_expression_tree.name().accept(*this, context); r =
m_visitor.visit(ident_expression_tree, accumulate(context, r)); return r;
}


void RecursivePostOrderVisitor::visit(LiteralTree& literal_tree, Context&
context) { return m_visitor.visit(literal_tree, context);
}


void RecursivePostOrderVisitor::visit(LValueIdentTree& lvalue_ident_tree,
Context& context) { void r = lvalue_ident_tree.name().accept(*this, context); r
= m_visitor.visit(lvalue_ident_tree, accumulate(context, r)); return r;
}


void RecursivePostOrderVisitor::visit(NameTree& name_tree, Context& context) {
  m_visitor.visit(name_tree, context);
}


void RecursivePostOrderVisitor::visit(NegateTree& negate_tree, Context& context)
{ void r = negate_tree.expression().accept(*this, context); r =
m_visitor.visit(negate_tree, accumulate(context, r)); return r;
}


void RecursivePostOrderVisitor::visit(ProgramTree& program_tree, Context&
context) {

  T d = context;
  for (auto& func : program_tree.topLevelTrees()) {
    r = func.accept(*this, d);
    d = accumulate(d, r);
  }
  r = m_visitor.visit(program_tree, d);
  return r;
}


void RecursivePostOrderVisitor::visit(ReturnTree& return_tree, Context& context)
{ void r = return_tree.expression().accept(*this, context); r =
m_visitor.visit(return_tree, accumulate(context, r)); return r;
}


void RecursivePostOrderVisitor::visit(TypeTree& type_tree, Context& context) {
  return m_visitor.visit(type_tree, context);
}


Context RecursivePostOrderVisitor::accumulate(Context& context) {
  return context;
}
*/
