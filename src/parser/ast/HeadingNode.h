#pragma once
#include "parser/ast/Node.h"
#include "parser/ast/TextNode.h"

namespace MiniEditor::parser {
class HeadingNode final : public Node {
 public:
  HeadingNode(size_t level, std::string text) : level_(level), text_(text) {
    if (level_ < 1 || level_ > 6) {
      throw std::invalid_argument{"Heading level must between 1 and 6"};
    }
  };
  [[nodiscard]]
  NodeType type() const noexcept override {
    return NodeType::Heading;
  }
  [[nodiscard]]
  size_t level() const noexcept {
    return level_;
  }
  [[nodiscard]]
  const TextNode& text() const noexcept {
    return text_;
  }

  void accept(Visitor& visitor) const override { visitor.visit(*this); }

 private:
  size_t level_;
  TextNode text_;
};
}  // namespace MiniEditor::parser
