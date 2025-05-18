#pragma once

#include "tree.h"
#include "name_tree.h"


class LValueTree: public Tree { };

class LValueIdentTree: public LValueTree {
    public:
     LValueIdentTree(std::unique_ptr<NameTree> name) : m_name(std::move(name)) {}
     Span span() const override { return m_name->span(); }
     void accept(Visitor& visitor, Context& context) override {
       visitor.visit(*this, context);
     };
    private:
     const std::unique_ptr<NameTree> m_name;
};