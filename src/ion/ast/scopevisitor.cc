#include "scopevisitor.h"

namespace ion {
namespace ast {

ScopeVisitor::ScopeVisitor()
{
    m_currentScope = new Scope(nullptr);
}

void ScopeVisitor::visitIn(PackageDecl *package) {
    package->scope = *m_currentScope;
}

void ScopeVisitor::visitIn(Import *import) {
    import->scope = *m_currentScope;
}

void ScopeVisitor::visitIn(FuncCall *funcCall) {
    funcCall->scope = *m_currentScope;
}

void ScopeVisitor::visitIn(FuncDecl *funcDecl) {
    m_currentScope->addDeclaration(funcDecl->name, funcDecl);
    m_currentScope = new Scope(m_currentScope);
    funcDecl->scope = *m_currentScope;
}

void ScopeVisitor::visitOut(FuncDecl *funcDecl) {
    memcpy(m_currentScope, m_currentScope->parent(), sizeof(m_currentScope));
}

void ScopeVisitor::visitIn(StringLiteral *stringLiteral) {
    stringLiteral->scope = *m_currentScope;
}

} // namespace ast
} // namespace ion
