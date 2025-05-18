#include "name.h"

std::unique_ptr<Name> Name::for_keyword(const Keyword& keyword) {
    return std::make_unique<KeywordName>(keyword.get_type());
}

std::unique_ptr<Name> Name::for_identifier(const Identifier& identifier) {
    return std::make_unique<IdentName>(identifier.as_string());
}
