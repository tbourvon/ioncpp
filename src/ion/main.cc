#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "ast/scopevisitor.h"
#include "ast/debugvisitor.h"
#include "ast/existencevisitor.h"

int main() {
    ion::Lexer lexer;
    std::vector<ion::Token> list = lexer.tokenize("package main \n"
                                                  "import 'io' \n"
                                                  "func main() { \n"
                                                       "print('Hello world!') \n"
                                                  "}");

    ion::Parser parser;
    std::vector<ion::ast::Node*> ast = parser.parse(list);
    ion::ast::ScopeVisitor svst;
    for (ion::ast::Node* node : ast) {
        node->accept(&svst);
    }
    ion::ast::DebugVisitor dvst;
    for (ion::ast::Node* node : ast) {
        node->accept(&dvst);
    }
    ion::ast::ExistenceVisitor evst;
    for (ion::ast::Node* node : ast) {
        node->accept(&evst);
    }
    return 0;
}

