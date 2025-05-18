#pragma once

#include "tree.h"
#include "name_tree.h"


class LValueTree: public Tree { };

class LValueIdentTree: public LValueTree {
    public:
     LValueIdentTree(std::unique_ptr<NameTree> name) : _name(std::move(name)) {}
     Span span() const override { return _name->span(); }
     void accept(Visitor& visitor, Context& context) override {
       visitor.visit(*this, context);
     };

     const std::unique_ptr<NameTree> _name;
};