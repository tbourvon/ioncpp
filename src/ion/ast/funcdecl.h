#ifndef ION_FUNCDECL_H
#define ION_FUNCDECL_H

#include <vector>
#include "../utf8string.h"
#include "declaration.h"
#include "expression.h"

namespace ion {
namespace ast {

struct FuncDecl : public Declaration {
public:
    struct Argument {
        utf8string type;
        utf8string name;
        Expression* defaultValue;
    };

    utf8string name;
    std::vector<Argument> arguments;
    std::vector<utf8string> returnTypes;
    std::vector<Node*> nodes;

    void accept(Visitor *visitor);
};

} // namespace ast
} // namespace ion

#endif // ION_FUNCDECL_H
