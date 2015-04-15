#include "stringliteral.h"

namespace ion {
namespace ast {

void StringLiteral::accept(Visitor *visitor) {
    visitor->visit(this);
}

} // namespace ast
} // namespace ion
