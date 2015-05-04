#include "existencevisitor.h"

namespace ion {
namespace ast {

void ExistenceVisitor::visitIn(PackageDecl *package) {

}

void ExistenceVisitor::visitIn(Import *import) {

}

void ExistenceVisitor::visitIn(FuncCall *funcCall) {
    if (!funcCall->scope.isInScope(funcCall->name))
        std::cout << "Unknown function " << funcCall->name << std::endl;
}

void ExistenceVisitor::visitIn(FuncDecl *funcDecl) {
    if (funcDecl->scope.isInScope(funcDecl->name))
        std::cout << "Function already defined: " << funcDecl->name << std::endl;
}

void ExistenceVisitor::visitOut(FuncDecl *funcDecl) {

}

void ExistenceVisitor::visitIn(StringLiteral *stringLiteral) {

}

} // namespace ast
} // namespace ion
