#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "ast/debugvisitor.h"

int main() {
    ion::Lexer lexer;
    std::vector<ion::Token> list = lexer.tokenize("package main \n"
                                                  "import 'io' \n"
                                                  "func main() { \n"
                                                       "io.print('Hello world!') \n"
                                                  "}");

    ion::Parser parser;
    std::vector<ion::ast::Node*> ast = parser.parse(list);
    ion::ast::DebugVisitor vst;
    for (ion::ast::Node* node : ast) {
        node->accept(&vst);
    }
    return 0;
}

