#include "funcdecl.h"

namespace ion {
namespace ast {

void FuncDecl::accept(Visitor *visitor) {
    visitor->visit(this);
}

} // namespace ast
} // namespace ion
