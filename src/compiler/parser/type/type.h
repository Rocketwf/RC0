#pragma once

#include <algorithm>
#include <string>

class Type {
 public:
  virtual ~Type() = default;
  virtual std::string as_string() const = 0;
};

enum class BasicTypeEnum { 
    INT 
};

class BasicType : public Type {
 private:
  BasicTypeEnum type;

 public:
  explicit BasicType(BasicTypeEnum type) : type(type) {}

  std::string as_string() const override {
    switch (type) {
      case BasicTypeEnum::INT:
        return "int";
      default:
        return "unknown";
    }
  }

  BasicTypeEnum get_type() const { return type; }
};
