#ifndef ION_TOKEN_H
#define ION_TOKEN_H

#include <initializer_list>
#include "utf8string.h"

namespace ion {

struct Token
{
    enum TokenType {
        Invalid,
        Identifier,
        Keyword,
        String,
        Integer,
        Float,
        Symbol
    };

    explicit operator bool() const {
        return (type != Invalid);
    }

    inline bool operator==(const Token& token) const {
        return (type == token.type && data == token.data);
    }

    TokenType type;
    utf8string data;
};

} // namespace ion

#endif // ION_TOKEN_H
