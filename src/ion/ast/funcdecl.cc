#include "funcdecl.h"

namespace ion {
namespace ast {

void FuncDecl::accept(Visitor *visitor) {
    visitor->visitIn(this);
    for (Node* node : nodes) {
        node->accept(visitor);
    }
    visitor->visitOut(this);
}

} // namespace ast
} // namespace ion
