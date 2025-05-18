#pragma once

#include "tree.h"
#include "compiler/parser/symbol/name.h"

class NameTree: public Tree {
    public:
     NameTree(std::unique_ptr<Name> name, Span span)
         : _name(std::move(name)), m_span(span) {}
     void accept(Visitor& visitor, Context& context) override {
       visitor.visit(*this, context);
     }
     Span span() const override {
        return m_span;
     }
     const std::unique_ptr<Name> _name;
     private:
     const Span m_span;
};