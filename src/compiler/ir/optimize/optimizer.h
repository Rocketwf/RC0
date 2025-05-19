#pragma once

#include "compiler/ir/node/node.h"

#include <memory>

class Optimizer {
    public:
    virtual std::unique_ptr<Node> transform(std::unique_ptr<Node> node) = 0;
}