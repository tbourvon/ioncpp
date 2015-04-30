#ifndef SCOPEVISITOR_H
#define SCOPEVISITOR_H

#include "visitor.h"
#include "scope.h"
#include "packagedecl.h"
#include "import.h"
#include "funccall.h"
#include "funcdecl.h"
#include "stringliteral.h"

namespace ion {
namespace ast {

class ScopeVisitor : public Visitor {
public:
    ScopeVisitor();

    virtual void visitIn(PackageDecl* package) override;
    virtual void visitIn(Import* import) override;
    virtual void visitIn(FuncCall* funcCall) override;
    virtual void visitIn(FuncDecl* funcDecl) override;
    virtual void visitOut(FuncDecl* funcDecl) override;
    virtual void visitIn(StringLiteral* stringLiteral) override;

private:
    Scope* m_currentScope;
};

} // namespace ast
} // namespace ion

#endif // SCOPEVISITOR_H
