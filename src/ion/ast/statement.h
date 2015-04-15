#ifndef ION_STATEMENT_H
#define ION_STATEMENT_H

#include "node.h"

namespace ion {
namespace ast {

struct Statement : public Node
{
    virtual void accept(Visitor *visitor) = 0;
};

} // namespace ast
} // namespace ion

#endif // ION_STATEMENT_H
