#include "statement_tree.h"

Span AssignmentTree::span() const {
  return _l_value_tree->span().merge(_expression_tree->span());
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
  if (_initializer != nullptr) {
    return _type_tree->span().merge(_initializer->span());
  }
  return _type_tree->span().merge(_name_tree->span());
}

void DeclarationTree::accept(Visitor& visitor, Context& context) {
  visitor.visit(*this, context);
}

Span ReturnTree::span() const {
  return Span(m_start, _expression->span().end());
}

void ReturnTree::accept(Visitor& visitor, Context& context) {
  visitor.visit(*this, context);
}
