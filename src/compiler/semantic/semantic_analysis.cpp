#include "semantic_analysis.h"

#include "integer_literal_range_analysis.h"
#include "compiler/parser/visitor/recursive_postorder_visitor.h"

#include <iostream>

std::unique_ptr<ProgramTree> SemanticAnalysis::analyze() {
    IntegerLiteralRangeAnalysis IRA;
    auto visitor = RecursivePostOrderVisitor(IRA);
    Context context;
    m_program->accept(visitor, context);

    return std::move(m_program);
}