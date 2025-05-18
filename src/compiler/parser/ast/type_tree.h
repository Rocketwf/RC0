#pragma once

#include "tree.h"
#include "compiler/parser/type/type.h"

class TypeTree: public Tree {
    public:
     TypeTree(std::unique_ptr<Type> type, Span span)
         : m_type(std::move(type)), m_span(span) {}

     void accept(Visitor& visitor, Context& context) override;
     Span span() const override;

    private:
     std::unique_ptr<Type> m_type;
     Span m_span;
};