/**
 * @file ParagraphNode.h
 * @author Alligator
 * @brief 段落节点：允许段内换行
 * @version 0.1
 * @date 2026-08-06
 * @copyright Copyright (c) 2026
 */

#pragma once
#include <string_view>

#include "parser/ast/Node.h"
#include "parser/ast/TextNode.h"

namespace mini::parser {
class ParagraphNode final : public Node {
 private:
  TextNode text_;

 public:
  explicit ParagraphNode(std::string_view text) : text_(text) {}

  [[nodiscard]]
  NodeType type() const noexcept override {
    return NodeType::Paragraph;
  }

  [[nodiscard]]
  const TextNode& text() const noexcept {
    return text_;
  }
};

}  // namespace mini::parser
