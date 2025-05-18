#include "type_tree.h"

void TypeTree::accept(Visitor& visitor, Context& context) {
  visitor.visit(*this, context);
}

Span TypeTree::span() const {
    return m_span;
}