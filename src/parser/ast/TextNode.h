/**
 * @file TextNode.h
 * @author Alligator
 * @brief 文本节点
 * @version 0.1
 * @date 2026-08-0
 * @copyright Copyright (c) 2026
 */
#pragma once
#include <string_view>
#include <utility>

#include "parser/ast/Node.h"

namespace mini::parser {
class TextNode final : public Node {
 public:
  explicit TextNode(const std::string_view text) : text_(text) {}
  [[nodiscard]]
  NodeType type() const noexcept override {
    return NodeType::Text;
  }

 private:
  std::string_view text_;
};
}  // namespace mini::parser
