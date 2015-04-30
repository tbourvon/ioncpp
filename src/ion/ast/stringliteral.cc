#include "stringliteral.h"

namespace ion {
namespace ast {

void StringLiteral::accept(Visitor *visitor) {
    visitor->visitIn(this);
}

} // namespace ast
} // namespace ion
