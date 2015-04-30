#ifndef DEBUGVISITOR_H
#define DEBUGVISITOR_H

#include <iostream>
#include "visitor.h"
#include "packagedecl.h"
#include "import.h"
#include "funccall.h"
#include "funcdecl.h"
#include "stringliteral.h"

namespace ion {
namespace ast {

class DebugVisitor : public Visitor {
public:
    virtual void visitIn(PackageDecl* package) override;
    virtual void visitIn(Import* import) override;
    virtual void visitIn(FuncCall* funcCall) override;
    virtual void visitIn(FuncDecl* funcDecl) override;
    virtual void visitOut(FuncDecl* funcDecl) override;
    virtual void visitIn(StringLiteral* stringLiteral) override;

private:
    utf8string m_indentation;
};

} // namespace ast
} // namespace ion

#endif // DEBUGVISITOR_H
