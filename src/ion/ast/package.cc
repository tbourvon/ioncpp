#include "package.h"

namespace ion {
namespace ast {

void Package::accept(Visitor *visitor) {
    visitor->visit(this);
}

} // namespace ast
} // namespace ion
