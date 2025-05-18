#pragma once 

#include "compiler/parser/visitor/context.h"
#include "../../span.h"
#include "../visitor/visitor.h"

class Visitor;

class Tree {
    public:
    virtual ~Tree() = default;
    virtual Span span() const = 0;
    virtual void accept(Visitor& visitor, Context& context) = 0;
};