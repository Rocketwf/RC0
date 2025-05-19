#pragma once

#include <vector>

#include "tree.h"
#include "function_tree.h"

#include <iostream>

class ProgramTree: public Tree {
    public:
     ProgramTree(std::vector<std::unique_ptr<FunctionTree>> top_level_trees)
         : _top_level_trees(std::move(top_level_trees)) {};
     void accept(Visitor& visitor, Context& context) override {
       visitor.visit(*this, context);
     }
     Span span() const override {
        auto first = _top_level_trees.front()->span();
        auto last = _top_level_trees.back()->span();
        return Span(first.start(), last.end());
     }
    std::vector<std::unique_ptr<FunctionTree>> _top_level_trees; //TODO: Possibly make const?
};