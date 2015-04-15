#ifndef ION_INTERPRETERVISITOR_H
#define ION_INTERPRETERVISITOR_H

#include <iostream>
#include <vector>
#include "visitor.h"
#include "node.h"
#include "funccall.h"
#include "stringliteral.h"
#include "funcdecl.h"

namespace ion {
namespace ast {

class InterpreterVisitor : public Visitor
{
public:
    virtual void visit(Package* package);
    virtual void visit(Import* import);
    virtual void visit(FuncCall* funcCall);
    virtual void visit(FuncDecl* funcDecl);
    virtual void visit(StringLiteral* stringLiteral);

    void run(std::vector<Node *> ast);

private:

};

} // namespace ast
} // namespace ion

#endif // ION_INTERPRETERVISITOR_H
