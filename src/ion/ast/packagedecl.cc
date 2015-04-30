#include "packagedecl.h"

namespace ion {
namespace ast {

void PackageDecl::accept(Visitor *visitor) {
    visitor->visitIn(this);
}

} // namespace ast
} // namespace ion
