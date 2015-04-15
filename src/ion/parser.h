#ifndef ION_PARSER_H
#define ION_PARSER_H

#include <vector>
#include <map>
#include <iostream>
#include <set>
#include "token.h"
#include "ast/node.h"
#include "ast/package.h"
#include "ast/import.h"
#include "utf8string.h"
#include "ast/funcdecl.h"
#include "ast/funccall.h"
#include "ast/stringliteral.h"

namespace ion {

/**
 * Handles the parsing of a Token vector, returning an AST (Abstract Syntax Tree).
 * This class is an LL(1) parser which follows the ion language specification. It parses a Token vector
 * and returns an AST, through the \ref parse() function.
 */
class Parser
{
public:
    std::vector<ast::Node*> parse(const std::vector<Token>& tokens);

private:
    std::vector<Token>::const_iterator m_itr;
    std::vector<ast::Node*> m_ast;

    std::set<utf8string> m_types = {
        "io"
    };

    Token lookahead(Token token);
    Token lookaheadType();
    Token expect(Token token);
    Token accept(Token token);
    Token acceptType();

    ast::Package *parsePackage();
    ast::Import *parseImport();
    ast::FuncDecl *parseFuncDecl();
    ast::FuncCall *parseFuncCall(utf8string context);
    utf8string parseType();
    ast::Expression *parseExpression();
};

} // namespace ion

#endif // ION_PARSER_H
