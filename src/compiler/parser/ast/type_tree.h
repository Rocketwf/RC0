#pragma once

#include "tree.h"
#include "compiler/parser/type/type.h"

class TypeTree: public Tree {
    public:
     TypeTree(std::unique_ptr<Type> type, Span span)
         : _type(std::move(type)), m_span(span) {}

     void accept(Visitor& visitor, Context& context) override;
     Span span() const override;

     const std::unique_ptr<Type> _type;
     private:
     const Span m_span;
};