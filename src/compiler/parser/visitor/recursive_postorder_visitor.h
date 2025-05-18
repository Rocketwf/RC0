#pragma once

#include "visitor.h"


//class RecursivePostOrderVisitor: public Visitor {
//    public:
//    RecursivePostOrderVisitor(Visitor& visitor):
//        m_visitor(visitor) {}
//
//    void visit(AssignmentTree& assignment_tree, Context& context) override;
//    
//    void visit(BinaryOperationTree& binary_operation_tree , Context& context) override;
//    
//    void visit(BlockTree& block_tree, Context& context) override;
//    
//    void visit(DeclarationTree& declaration_tree, Context& context) override;
//    
//    void visit(FunctionTree& function_tree, Context& context) override;
//    
//    void visit(IdentExpressionTree& ident_expression_tree, Context& context) override;
//    
//    void visit(LiteralTree& literal_tree, Context& context) override;
//    
//    void visit(LValueIdentTree& lvalue_ident_tree, Context& context) override;
//    
//    void visit(NameTree& name_tree, Context& context) override;
//    
//    void visit(NegateTree& negate_tree, Context& context) override;
//    
//    void visit(ProgramTree& program_tree, Context& context) override;
//    
//    void visit(ReturnTree& return_tree, Context& context) override;
//    
//    void visit(TypeTree& type_tree, Context& context) override;
//    private:
//    Context accumulate(Context& context);
//    const Visitor& m_visitor;
//
//};
