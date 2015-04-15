#ifndef ION_PACKAGE_H
#define ION_PACKAGE_H

#include "../utf8string.h"
#include "statement.h"

namespace ion {
namespace ast {

struct Package : public Statement
{
    utf8string name;

    void accept(Visitor *visitor);
};

} // namespace ast
} // namespace ion

#endif // ION_PACKAGE_H
