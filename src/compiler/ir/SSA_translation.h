#pragma once

#include "graph_constructor.h"
#include "compiler/parser/ast/function_tree.h"
#include "compiler/ir/optimize/optimizer.h"

class SSATranslation {
    public:
     SSATranslation(std::unique_ptr<FunctionTree> function,
                    std::unique_ptr<Optimizer> optimizer): m_function(std::move(function)) {
        m_constuctor = std::make_unique<GraphConstructor>(optimizer, function->_name->_name->as_string());
     }

    private:
    std::unique_ptr<FunctionTree> m_function;
    std::unique_ptr<GraphConstructor> m_constructor;
};