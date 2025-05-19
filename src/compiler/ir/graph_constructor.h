#pragma once

#include <memory>
#include <unordered_map>


#include "compiler"
#include "IR_graph.h"

class GraphConstructor {
public:
private:
    std::unique_ptr<Optimizer> optimizer;
    std::unique_ptr<IRGraph> graph;
    std::unordered_map<Name
};