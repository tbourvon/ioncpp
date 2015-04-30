#ifndef DECLARATION_H
#define DECLARATION_H

#include "statement.h"

namespace ion {
namespace ast {

struct Declaration : public Statement {
    virtual void accept(Visitor *visitor) = 0;
};

} // namespace ast
} // namespace ion

#endif // DECLARATION_H
