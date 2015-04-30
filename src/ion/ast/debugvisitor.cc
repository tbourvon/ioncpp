#include "debugvisitor.h"

namespace ion {
namespace ast {

void DebugVisitor::visitIn(PackageDecl *package) {
    std::cout << m_indentation << "PackageDecl: {"
              << "name: " << package->name
              << "}" << std::endl;
}

void DebugVisitor::visitIn(Import *import) {
    std::cout << m_indentation << "Import: {"
              << "path: " << import->path
              << "}" << std::endl;
}

void DebugVisitor::visitIn(FuncCall *funcCall) {
    std::cout << m_indentation << "FuncCall: {"
              << "name: " << funcCall->name << ", "
              << "arguments: " << funcCall->arguments.size()
              << "}" << std::endl;
}

void DebugVisitor::visitIn(FuncDecl *funcDecl) {
    std::cout << m_indentation << "FuncDecl: {"
              << "name: " << funcDecl->name << ", "
              << "arguments: " << funcDecl->arguments.size() << ", "
              << "returnTypes: " << funcDecl->returnTypes.size() << ", "
              << "nodes: " << funcDecl->nodes.size()
              << "}" << std::endl;
    m_indentation += " - ";
}

void DebugVisitor::visitOut(FuncDecl *funcDecl) {
    // TODO: remove indendation
}

void DebugVisitor::visitIn(StringLiteral *stringLiteral) {
    std::cout << m_indentation << "StringLiteral: {"
              << "string: " << stringLiteral->string
              << "}" << std::endl;
}

} // namespace ast
} // namespace ion
