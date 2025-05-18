#pragma once

#include "type_tree.h"
#include "name_tree.h"
#include "statement_tree.h"

class FunctionTree: public Tree {
    public:
     FunctionTree(std::unique_ptr<TypeTree> return_type,
                  std::unique_ptr<NameTree> name,
                  std::unique_ptr<BlockTree> body)
         : _return_type(std::move(return_type)),
           _name(std::move(name)),
           _body(std::move(body)) {};
     Span span() const override {
       return Span(_return_type->span().start(), _return_type->span().end());
     }
    void accept(Visitor& visitor, Context& context) override {
        visitor.visit(*this, context);
    };

    const std::unique_ptr<TypeTree> _return_type;
    const std::unique_ptr<NameTree> _name;
    const std::unique_ptr<BlockTree> _body;
};