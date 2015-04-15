#ifndef ION_IMPORT_H
#define ION_IMPORT_H

#include "../utf8string.h"
#include "statement.h"

namespace ion {
namespace ast {

struct Import : public Statement
{
    utf8string path;

    void accept(Visitor *visitor);
};

} // namespace ast
} // namespace ion

#endif // ION_IMPORT_H
