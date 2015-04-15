#include "import.h"

namespace ion {
namespace ast {

void Import::accept(Visitor *visitor) {
    visitor->visit(this);
}

} // namespace ast
} // namespace ion
