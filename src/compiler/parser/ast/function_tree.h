#pragma once

#include "type_tree.h"
#include "name_tree.h"
#include "statement_tree.h"

class FunctionTree: public Tree {
    public:
     FunctionTree(std::unique_ptr<TypeTree> return_type,
                  std::unique_ptr<NameTree> name,
                  std::unique_ptr<BlockTree> body)
         : m_return_type(std::move(return_type)),
           m_name(std::move(name)),
           m_body(std::move(body)) {};
     Span span() const override {
       return Span(m_return_type->span().start(), m_return_type->span().end());
     }
    void accept(Visitor& visitor, Context& context) override {
        visitor.visit(*this, context);
    };

    private:
     const std::unique_ptr<TypeTree> m_return_type;
     const std::unique_ptr<NameTree> m_name;
     const std::unique_ptr<BlockTree> m_body;
};