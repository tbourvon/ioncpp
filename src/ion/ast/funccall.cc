#include "funccall.h"

namespace ion {
namespace ast {

void FuncCall::accept(Visitor *visitor) {
    visitor->visitIn(this);
}

} // namespace ast
} // namespace ion
