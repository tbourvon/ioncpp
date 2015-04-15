#include "parser.h"

namespace ion {

/**
 * Parses the given Token vector, and returns an AST (Abstract Syntax Tree).
 * This function parses the top-level nodes of the program, then delegates the parsing of deeper nodes to the recursive
 * parsing functions of each element. The top-level nodes are added to the resulting vector, which is then returned.
 * \param tokens A Token vector to be parsed.
 * \return The produced AST.
 */
std::vector<ast::Node *> Parser::parse(const std::vector<Token> &tokens) {
    m_itr = tokens.cbegin();
    while (m_itr != tokens.cend()) {
        if (accept({Token::Keyword, "package"}))
            m_ast.push_back(parsePackage());
        else if (accept({Token::Keyword, "import"}))
            m_ast.push_back(parseImport());
        else if (accept({Token::Keyword, "func"}))
            m_ast.push_back(parseFuncDecl());
        else
            break;
    }

    return m_ast;
}

/**
 * Checks the next Token against a given Token.
 * This function compares a given Token to the next Token to be parsed (peeking), resulting in a LL(1) parsing.
 * If the Tokens match, then the next Token is returned. Else, an invalid Token is returned.
 * \param token A Token to check the next Token against.
 * \return The matched Token if found, else an invalid Token.
 */
Token Parser::lookahead(Token token) {
    if ((token.data == "" && (*(m_itr + 1)).type == token.type) || ((*(m_itr + 1)) == token))
        return *(m_itr + 1);

    return {Token::Invalid, ""};
}


/**
 * Checks whether the next Token is a type or not.
 * This function tries to find the next Token in the types set, and returns the Token if successful. Else, it returns
 * an invalid Token.
 * \return The matched Token if it is a type, else an invalid Token.
 */
Token Parser::lookaheadType() {
    for (utf8string type : m_types) {
        Token typeToken = lookahead({Token::Identifier, type});
        if (typeToken)
            return typeToken;
    }

    return {Token::Invalid, ""};
}

/**
 * Expects the current Token to match a given Token.
 * This function compares the current Token against a given Token. If the Token matches, it is returned, else an error
 * is triggered and an invalid Token is returned.
 * \param token A token to check the current Token against.
 * \return The matched Token if found, else an invalid Token.
 */
Token Parser::expect(Token token) {
    Token ret = accept(token);
    if (!ret)
        std::cout << "Error: expected " << token.type << " : " << token.data << " got " << (*m_itr).type << " : " << (*m_itr).data << std::endl;
    return ret;
}

/**
 * Checks the current Token against the given Token.
 * This function compares the given Token to the current Token. If the Tokens match, then the current Token is returned.
 * Else, and invalid Token is returned.
 * \param token The token to check the current Token against.
 * \return The matched Token if found, else an invalid Token.
 */
Token Parser::accept(Token token) {
    if ((token.data == "" && (*m_itr).type == token.type) || ((*m_itr) == token))
        return *(m_itr++);

    while ((*m_itr) == Token{Token::Symbol, "\n"})
        ++m_itr;

    return {Token::Invalid, ""};
}

/**
 * Checks whether the current Token is a type or not.
 * This function tried to find the current Token in the types set, and returns the Token if successful. Else it returns
 * an invalid Token.
 * \return The matched Token if it is a type, else an invalid Token.
 */
Token Parser::acceptType() {
    for (utf8string type : m_types) {
        Token typeToken = accept({Token::Identifier, type});
        if (typeToken)
            return typeToken;
    }

    return {Token::Invalid, ""};
}

/**
 * Parses a package declaration as defined in the specification.
 * A package declaration takes the following form:
 *
 *     "package" <package-name>
 *
 *
 * Example:
 *
 *     package main
 *
 * \return The package AST node.
 */
ast::Package* Parser::parsePackage() {
    ast::Package* package = new ast::Package;
    package->name = expect({Token::Identifier, ""}).data;
    return package;
}

/**
 * Parses an import statement as defined in the specification.
 * An import statement takes the following form:
 *
 *     "import" lq <import-path> rq
 *
 *
 * Example:
 *
 *     import 'io'
 *
 * \return The import AST node.
 */
ast::Import* Parser::parseImport() {
    ast::Import* import = new ast::Import;
    import->path = expect({Token::String, ""}).data;
    return import;
}

/**
 * Parses a function declaration as defined in the specification.
 * A function declaration takes the following form:
 *
 *     "func" <function-name> "(" { <argument-type> <argument-name> ["=" <argument-default-value>] "," } ")" "->" <return-type> "{"
 *         { <node> }
 *     "}"
 *
 *
 * Example:
 *
 *     func multiply(int a, int b = 2) -> int {
 *         ret a * b
 *     }
 *
 * \return The function declaration AST node.
 */
ast::FuncDecl* Parser::parseFuncDecl() {
    ast::FuncDecl* funcDecl = new ast::FuncDecl;

    // We first parse the definition.

    funcDecl->name = expect({Token::Identifier, ""}).data;

    expect({Token::Symbol, "("});
    bool firstArg = true; // We use firstArg so that we don't have to add a heading/trailing comma.
    while (!accept({Token::Symbol, ")"})) {
        if (!firstArg)
            expect({Token::Symbol, ","});
        else
            firstArg = false;

        ast::FuncDecl::Argument argument;
        argument.type = expect({Token::Identifier, ""}).data;
        argument.name = expect({Token::Identifier, ""}).data;
        argument.defaultValue = accept({Token::Symbol, "="}) ? parseExpression() : nullptr;
        funcDecl->arguments.push_back(argument);
    }

    if (accept({Token::Symbol, "->"})) // The return type definition is optional
        funcDecl->returnTypes.push_back(expect({Token::Identifier, ""}).data);

    // Now we parse the nodes block.

    expect({Token::Symbol, "{"});
    while (!accept({Token::Symbol, "}"})) {
        utf8string type = parseType();
        Token varDeclNameToken = accept({Token::Identifier, ""});
        if (type != "" && accept({Token::Symbol, "."})) {
            if (lookahead({Token::Symbol, "("}))
                funcDecl->nodes.push_back(parseFuncCall(type));
        } else if (type != "" && varDeclNameToken) {

        }
    }

    return funcDecl;
}

/**
 * Parses a function call as defined in the specification.
 * A function call takes the following form:
 *
 *     <function-context> "." <function-name> "(" { <argument> "," } ")"
 *
 *
 * Example:
 *
 *     io.print("Hello world!")
 *
 * \param context the context/owner of the function.
 * \return The function call node.
 */
ast::FuncCall *Parser::parseFuncCall(utf8string context) {
    ast::FuncCall* funcCall = new ast::FuncCall;

    funcCall->name = context + "." + expect({Token::Identifier, ""}).data;

    expect({Token::Symbol, "("});
    bool firstArg = true; // We use firstArg so that we don't have to add a heading/trailing comma.
    while (!accept({Token::Symbol, ")"})) {
        if (!firstArg)
            expect({Token::Symbol, ","});
        else
            firstArg = false;

        funcCall->arguments.push_back(parseExpression());
    }

    return funcCall;
}

/**
 * Parses a type.
 * \return The parsed type.
 */
utf8string Parser::parseType() {
    utf8string type;

    while (Token typeToken = acceptType()) {
        type += typeToken.data;
        if (lookaheadType())
            type += accept({Token::Symbol, "."}).data;
    }

    return type;
}

/**
 * Parses an expression as defined in the specification.
 * An expression is a node that can be evaluated to a certain value of a certain type.
 * \return The expression node.
 */
ast::Expression *Parser::parseExpression() {
    ast::Expression* expression;

    Token stringLiteralToken = accept({Token::String, ""});
    if (stringLiteralToken) {
        ast::StringLiteral* stringLiteral = new ast::StringLiteral;
        stringLiteral->string = stringLiteralToken.data;
        expression = stringLiteral;
    }

    return expression;
}

}

