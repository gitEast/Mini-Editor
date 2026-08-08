/**
 * @file TextNode.h
 * @author Alligator
 * @brief 文本节点
 * @version 0.1
 * @date 2026-08-0
 * @copyright Copyright (c) 2026
 */
#pragma once
#include <string>
#include <utility>

#include "parser/ast/Node.h"

namespace mini::parser {
class TextNode final : public Node {
 public:
  explicit TextNode(const std::string text) : text_(std::move(text)) {}

  [[nodiscard]]
  NodeType type() const noexcept override {
    return NodeType::Text;
  }

  [[nodiscard]]
  const std::string& text() const noexcept {
    return text_;
  }

 private:
  std::string text_;
};
}  // namespace mini::parser
