#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include "../utf8string.h"

namespace ion {
namespace ast {

class Declaration;

class Scope {
public:
    Scope() : m_parent(nullptr) {}
    explicit Scope(Scope* parent) : m_parent(parent) {}

    bool isInScope(utf8string identifier) const {
        return m_scope.count(identifier) != 0 || (m_parent != nullptr && m_parent->isInScope(identifier));
    }

    Declaration* getDeclaration(utf8string identifier) const {
        if (m_scope.count(identifier) != 0)
            return m_scope.at(identifier);
        else
            return nullptr;
    }

    void addDeclaration(utf8string identifier, Declaration* decl) {
        m_scope[identifier] = decl;
    }

    Scope* parent() {
        return m_parent;
    }

private:
    Scope* m_parent;
    std::map<utf8string, Declaration*> m_scope;
};

} // namespace ast
} // namespace ion

#endif // SCOPE_H
