#include "interpretervisitor.h"

namespace ion {
namespace ast {

void InterpreterVisitor::visit(Package *package)
{

}

void InterpreterVisitor::visit(Import *import)
{

}

void InterpreterVisitor::visit(FuncCall *funcCall)
{
    if (funcCall->name == "io.print")
        std::cout << ((StringLiteral*)funcCall->arguments.at(0))->string << std::endl;
}

void InterpreterVisitor::visit(FuncDecl *funcDecl)
{
    for (Node* node : funcDecl->nodes) {
        node->accept(this);
    }
}

void InterpreterVisitor::visit(StringLiteral *stringLiteral)
{

}

void InterpreterVisitor::run(std::vector<Node*> ast)
{
    for (Node* node : ast) {
        node->accept(this);
    }
}

} // namespace ast
} // namespace ion
