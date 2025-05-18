#include "expression_tree.h"
#include "compiler/span.h"
#include "compiler/parser/parse_exception.h"

Span BinaryOperationTree::span() const {
  return m_lhs->span().merge(m_rhs->span());
}

Span IdentExpressionTree::span() const {
  return m_name->span();
}

Span LiteralTree::span() const { return m_span; }

Span NegateTree::span() const {
  return m_minus_pos;
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
  int end = m_value.length();
  switch(m_base) {
    case 10: parse_dec(end); break;
    case 16: parse_hex(end); break;
    default:
      throw ParseException("unexpected base " + m_base);
  }  
}

std::optional<long> LiteralTree::parse_dec(int end) const {
  try {
      // Substring from index 0 to end (not inclusive)
      std::string sub = m_value.substr(0, end);
      long l = std::stol(sub, nullptr, m_base);

      if (l < 0 || static_cast<unsigned long>(l) > static_cast<unsigned long>(INT_MIN)) {
          return std::nullopt;
      }
      return l;
  } catch (const std::invalid_argument& e) {
      return std::nullopt;
  } catch (const std::out_of_range& e) {
      return std::nullopt;
}

}

std::optional<long> LiteralTree::parse_hex(int end) const {
  try {
    std::string sub = m_value.substr(2, end - 2);
    unsigned int result = std::stoul(sub, nullptr, 16);
    return static_cast<long>(result);
  } catch (const std::invalid_argument& e) {
      return std::nullopt;
  } catch (const std::out_of_range& e) {
      return std::nullopt;
  }
}
