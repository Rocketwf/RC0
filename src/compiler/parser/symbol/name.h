#pragma once

#include <memory>
#include <string>
#include <variant>

#include "../../lexer/keyword.h"
#include "../../lexer/identifier.h"

class KeywordName;
class IdentName;

class Name {
    public:
    virtual std::string as_string() const = 0;
    virtual ~Name () = default;
    
    static std::unique_ptr<Name> for_keyword(const Keyword& keyword);
    static std::unique_ptr<Name> for_identifier(const Identifier& identifier);
};

class KeywordName final: public Name {
    public:
    explicit KeywordName(const KeywordType type): m_type(type) {}
    std::string as_string() const override { 
        return Keyword::keywords[m_type]; 
    }
    private:
    KeywordType m_type;
};

class IdentName final: public Name {
    public:
    explicit IdentName(const std::string identifier) : m_identifier(identifier) {}
    std::string as_string() const override { return m_identifier; }

    private:
    std::string m_identifier;
};
