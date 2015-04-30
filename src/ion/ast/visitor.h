#ifndef ION_VISITOR_H
#define ION_VISITOR_H

namespace ion {
namespace ast {

class PackageDecl;
class Import;
class FuncCall;
class FuncDecl;
class StringLiteral;

class Visitor {
public:
    virtual void visitIn(PackageDecl* package) = 0;
    virtual void visitIn(Import* import) = 0;
    virtual void visitIn(FuncCall* funcCall) = 0;
    virtual void visitIn(FuncDecl* funcDecl) = 0;
    virtual void visitOut(FuncDecl* funcDecl) = 0;
    virtual void visitIn(StringLiteral* stringLiteral) = 0;
};

} // namespace ast
} // namespace ion

#endif // ION_VISITOR_H
