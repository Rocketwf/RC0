#pragma once

#include <vector>

#include "tree.h"
#include "function_tree.h"


class ProgramTree: public Tree {
    public:
     ProgramTree(std::vector<std::unique_ptr<FunctionTree>> top_level_trees)
         : m_top_level_trees(std::move(top_level_trees)) {};
     void accept(Visitor& visitor, Context& context) override {
       visitor.visit(*this, context);
     }
     Span span() const override {
        auto first = m_top_level_trees.front()->span();
        auto last = m_top_level_trees.back()->span();
        return Span(first.start(), last.end());
     }
    private:
    std::vector<std::unique_ptr<FunctionTree>> m_top_level_trees;
};