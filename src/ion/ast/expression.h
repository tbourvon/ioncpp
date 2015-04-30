#ifndef ION_EXPRESSION_H
#define ION_EXPRESSION_H

#include "node.h"

namespace ion {
namespace ast {

struct Expression : public Node {
    virtual void accept(Visitor *visitor) = 0;
};

} // namespace ast
} // namespace ion


#endif // ION_EXPRESSION_H
