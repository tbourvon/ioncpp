#ifndef ION_LEXER_H
#define ION_LEXER_H

#include <vector>
#include <set>
#include <iostream>
#include "utf8string.h"
#include "token.h"

namespace ion {

/**
 * Handles the tokenizing of a \ref utf8string into a vector or Token.
 * This class is a lexer/tokenizer which follows the ion language specification. It parses a \ref utf8string
 * and returns a vector of Token, through the \ref tokenize() function.
 */
class Lexer {
public:
    std::vector<ion::Token> tokenize(const utf8string& str);

private:
    utf8string m_buffer {""};
    utf8string::const_iterator m_itr = m_buffer.cbegin();
    utf8string m_currentToken {""};
    std::vector<ion::Token> m_tokens;

    std::set<utf8string> m_keywords = {
        "import",
        "package",
        "func"
    };

    std::set<utf8string> m_symbols = {
        "\n",
        ".",
        "{",
        "}",
        "(",
        ")"
    };

    void readWord();
    void readNumber();
    void readString(utfchar quote);
    void readSymbol();

    void skipWhitespace();
};

} // namespace ion

#endif // ION_LEXER_H
