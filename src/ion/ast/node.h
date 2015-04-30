#ifndef ION_NODE_H
#define ION_NODE_H

#include "visitor.h"
#include "scope.h"

namespace ion {
namespace ast {

struct Node {
    Scope scope;

    virtual void accept(Visitor* visitor) = 0;
};

} // namespace ast
} // namespace ion

#endif // ION_NODE_H
