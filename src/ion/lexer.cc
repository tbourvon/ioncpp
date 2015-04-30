#include "lexer.h"

namespace ion {

/**
 * Tokenizes the given \ref utf8string, and returns a Token vector.
 * This functions tokenizes the given UTF8 string, discarding whitespaces (except newlines, and in-string whitespace).
 * \param str A string to be tokenized.
 * \return A Token vector.
 */
std::vector<Token> Lexer::tokenize(const utf8string &str) {
    m_buffer = str;
    m_itr = m_buffer.cbegin();

    while (m_itr != m_buffer.cend()) {
        skipWhitespace();
        m_currentToken = "";

        if (('A' <= *m_itr && *m_itr <= 'Z') || ('a' <= *m_itr && *m_itr <= 'z') || *m_itr == '_' || *m_itr > 127)
            readWord();
        else if ('0' <= *m_itr && *m_itr <= '9')
            readNumber();
        else if (*m_itr == '"' || *m_itr == '\'')
            readString(*m_itr);
        else
            readSymbol();
    }

    return m_tokens;
}

/**
 * Reads a word (i.e. Keyword or Identifier) as defined in the specification.
 * A word starts with a letter, an underscore, or any UTF character > 127. It cannot start with a digit.
 * It can then contain letters, underscores, digits, and any UTF character > 127.
 */
void Lexer::readWord() {
    do {
        m_currentToken += *m_itr;
        ++m_itr;
    } while (('A' <= *m_itr && *m_itr <= 'Z') || ('a' <= *m_itr && *m_itr <= 'z') || ('0' <= *m_itr && *m_itr <= '9') || *m_itr == '_' || *m_itr > 127);
    if (m_keywords.count(m_currentToken) != 0)
        m_tokens.push_back({Token::Keyword, m_currentToken});
    else
        m_tokens.push_back({Token::Identifier, m_currentToken});
}

/**
 * Reads a number (i.e. Integer or Float) as defined in the specification.
 * An integer is composed of one or more digits.
 * A float is a composed of zero, one or more digits, then a point, then zero, one or more digits.
 */
void Lexer::readNumber() { // TODO: handle floats starting with a dot
    bool floatingPoint = false;
    do {
        if (*m_itr == '.') {
            if (floatingPoint) {
                m_tokens.push_back({Token::Float, m_currentToken});
                return;
            } else
                floatingPoint = true;
        }
        m_currentToken += *m_itr;
        ++m_itr;
    } while ('0' <= *m_itr && *m_itr <= '9' || *m_itr == '.');

    if (floatingPoint)
        m_tokens.push_back({Token::Float, m_currentToken});
    else
        m_tokens.push_back({Token::Integer, m_currentToken});
}

/**
 * Reads a String as defined in the specification.
 * An integer is composed of zero, one, or more UTF characters, enclosed between two single-quotes or double-quotes.
 * \param quote a quote character.
 */
void Lexer::readString(utfchar quote) {
    ++m_itr;
    do {
        m_currentToken += *m_itr;
        ++m_itr;
    } while (!(*m_itr == quote && m_currentToken.back() != '\\'));
    ++m_itr;
    m_tokens.push_back({Token::String, m_currentToken});
}

/**
 * Reads a Symbol as defined in the specification.
 * Newlines count as symbols.
 */
void Lexer::readSymbol() {
    std::set<utf8string> candidates;
    while (m_itr != m_buffer.cend()) {
        candidates.clear();
        for (utf8string symbol : m_symbols) {
            if (symbol.begins_with(m_currentToken + *m_itr))
                candidates.insert(symbol);
        }

        if (candidates.size() != 0) {
            m_currentToken += *m_itr;
            ++m_itr;
        } else if (m_symbols.count(m_currentToken) != 0)
            break;
        else {
            std::cout << "Unknown symbol: " << m_currentToken << std::endl;
            return;
        }
    }
    m_tokens.push_back({Token::Symbol, m_currentToken});
}

/**
 * Skips all whitespaces as defined in the specification.
 * The whitespaces are the space ' ', the tab '\\t' and the line return '\\r'.
 */
void Lexer::skipWhitespace() {
    while (*m_itr == ' ' || *m_itr == '\t' || *m_itr == '\r')
        ++m_itr;
}

} // namespace ion
