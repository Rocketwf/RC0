#pragma once

#include <string>

class Token {
    public:
        virtual bool is_keyword() const {
            return false;
        }
        virtual bool is_operator() const {
            return false;
        }
        virtual bool is_separator() const {
            return false;
        }
        virtual std::string asString() = 0;
};