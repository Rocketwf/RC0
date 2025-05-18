#include "statement_tree.h"

Span AssignmentTree::span() const {
  return m_l_value_tree->span().merge(m_expression_tree->span());
}

void AssignmentTree::accept(Visitor& visitor, Context& context) {
  visitor.visit(*this, context);
}

Span BlockTree::span() const {
  return m_span;
}

void BlockTree::accept(Visitor& visitor, Context& context) {
  visitor.visit(*this, context);
}

Span DeclarationTree::span() const {
  if (m_initializer != nullptr) {
    return m_type_tree->span().merge(m_initializer->span());
  }
  return m_type_tree->span().merge(m_name_tree->span());
}

void DeclarationTree::accept(Visitor& visitor, Context& context) {
  visitor.visit(*this, context);
}

Span ReturnTree::span() const {
  return Span(m_start, m_expression->span().end());
}

void ReturnTree::accept(Visitor& visitor, Context& context) {
  visitor.visit(*this, context);
}
