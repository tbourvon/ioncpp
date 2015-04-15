#ifndef ION_VISITOR_H
#define ION_VISITOR_H

namespace ion {
namespace ast {

class Package;
class Import;
class FuncCall;
class FuncDecl;
class StringLiteral;

class Visitor
{
public:
    virtual void visit(Package* package) = 0;
    virtual void visit(Import* import) = 0;
    virtual void visit(FuncCall* funcCall) = 0;
    virtual void visit(FuncDecl* funcDecl) = 0;
    virtual void visit(StringLiteral* stringLiteral) = 0;
};

} // namespace ast
} // namespace ion

#endif // ION_VISITOR_H
