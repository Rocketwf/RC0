#include "integer_literal_range_analysis.h"

#include "compiler/parser/ast/expression_tree.h"
#include "semantic_exception.h"

void IntegerLiteralRangeAnalysis::visit(LiteralTree& literal_tree,
                                        Context& context) {
    auto a = literal_tree.parse_value();
    if(!a.has_value()) {
        throw SemanticException("invalid integer literal: " + literal_tree._value);
    }
    return NoOpVisitor::visit(literal_tree, context);
}