#include "expression_tree.h"
#include "compiler/span.h"
#include "compiler/parser/parse_exception.h"
#include <limits>

Span BinaryOperationTree::span() const {
  return _lhs->span().merge(_rhs->span());
}

Span IdentExpressionTree::span() const {
  return _name->span();
}

Span LiteralTree::span() const { return _span; }

Span NegateTree::span() const {
  return _minus_pos;
}

void BinaryOperationTree::accept(Visitor& visitor, Context& context) {
  visitor.visit(*this, context);
}

void IdentExpressionTree::accept(Visitor& visitor, Context& context) {
  visitor.visit(*this, context);
}

void LiteralTree::accept(Visitor& visitor, Context& context) {
  visitor.visit(*this, context);
}

void NegateTree::accept(Visitor& visitor, Context& context) {
  visitor.visit(*this, context);
}


std::optional<long> LiteralTree::parse_value() { 
  int end = _value.length();
  switch(_base) {
<<<<<<< HEAD
<<<<<<< HEAD
    case 10: return parse_dec(end); break;
    case 16: return parse_hex(end); break;
    default:
      throw ParseException("unexpected base " + std::to_string(_base));
  }
=======
    case 10: parse_dec(end); break;
    case 16: parse_hex(end); break;
    default:
      throw ParseException("unexpected base " + _base);
  }  
>>>>>>> b5aa999 (bug)
=======
    case 10: return parse_dec(end); break;
    case 16: return parse_hex(end); break;
    default:
      throw ParseException("unexpected base " + std::to_string(_base));
  }
>>>>>>> dedd175 (fix missing return)
}

std::optional<long> LiteralTree::parse_dec(int end) const {
  try {
      // Substring from index 0 to end (not inclusive)
      std::string sub = _value.substr(0, end);
      long l = std::stol(sub, nullptr, _base);

      if (l < std::numeric_limits<int>::min() ||
          l > std::numeric_limits<int>::max()) {
          return std::nullopt;
      }
      return l;
  } catch (const std::invalid_argument& e) {
      return std::nullopt;
  } catch (const std::out_of_range& e) {
      return std::nullopt;
  }
  return std::nullopt;
}

std::optional<long> LiteralTree::parse_hex(int end) const {
  try {
    std::string sub = _value.substr(2, end - 2);
    unsigned int result = std::stoul(sub, nullptr, 16); //TODO: Perform check here too?
    return static_cast<long>(result);
  } catch (const std::invalid_argument& e) {
      return std::nullopt;
  } catch (const std::out_of_range& e) {
      return std::nullopt;
  }
  return std::nullopt;
}
