#include "import.h"

namespace ion {
namespace ast {

void Import::accept(Visitor *visitor) {
    visitor->visitIn(this);
}

} // namespace ast
} // namespace ion
