#include "funccall.h"

namespace ion {
namespace ast {

void FuncCall::accept(Visitor *visitor) {
    visitor->visit(this);
}

} // namespace ast
} // namespace ion
