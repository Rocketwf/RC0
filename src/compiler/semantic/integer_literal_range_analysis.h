#pragma once

#include "compiler/parser/visitor/no_op_visitor.h"

class IntegerLiteralRangeAnalysis: public NoOpVisitor {
    void visit(LiteralTree& literal_tree, Context& context) override;
};