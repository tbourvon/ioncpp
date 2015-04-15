#ifndef ION_STRINGLITERAL_H
#define ION_STRINGLITERAL_H

#include "../utf8string.h"
#include "expression.h"

namespace ion {
namespace ast {

struct StringLiteral : public Expression
{
    utf8string string;

    void accept(Visitor *visitor);
};

} // namespace ast
} // namespace ion

#endif // ION_STRINGLITERAL_H
