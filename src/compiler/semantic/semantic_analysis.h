#pragma once

#include <memory>

#include "compiler/parser/ast/program_tree.h"

class SemanticAnalysis {
    public:
    SemanticAnalysis(std::unique_ptr<ProgramTree> program): m_program(std::move(program)) {}
    std::unique_ptr<ProgramTree> analyze();
    private:
    std::unique_ptr<ProgramTree> m_program;
    Context m_context;
};