#ifndef ION_PACKAGEDECL_H
#define ION_PACKAGEDECL_H

#include "../utf8string.h"
#include "statement.h"

namespace ion {
namespace ast {

struct PackageDecl : public Statement
{
    utf8string name;

    virtual void accept(Visitor *visitor);
};

} // namespace ast
} // namespace ion

#endif // ION_PACKAGEDECL_H
