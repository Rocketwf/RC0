#pragma once

#include <stdexcept>

class SemanticException: public std::runtime_error {
 public:
    explicit SemanticException(const std::string& msg) : std::runtime_error(msg) {}
};