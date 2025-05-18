#pragma once

#include <stdexcept>

class ParseException : public std::runtime_error {
 public:
  explicit ParseException(const std::string& msg) : std::runtime_error(msg) {}
};