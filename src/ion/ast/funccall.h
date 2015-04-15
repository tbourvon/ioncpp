#ifndef ION_FUNCCALL_H
#define ION_FUNCCALL_H

#include <vector>
#include "../utf8string.h"
#include "statement.h"
#include "expression.h"

namespace ion {
namespace ast {

struct FuncCall : public Statement
{ 
    utf8string name;
    std::vector<Expression*> arguments;

    void accept(Visitor *visitor);
};

} // namespace ast
} // namespace ion

#endif // ION_FUNCCALL_H
