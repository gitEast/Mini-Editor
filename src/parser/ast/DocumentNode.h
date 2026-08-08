/**
 * @file DocumentNode.h
 * @author Alligator
 * @brief Document 节点：容器节点
 * @version 0.1
 * @date 2026-08-06
 * @copyright Copyright (c) 2026
 */
#pragma once

#include <memory>
#include <vector>

#include "parser/ast/Node.h"

namespace MiniEditor::parser {
class DocumentNode final : public Node {
 private:
  std::vector<std::unique_ptr<Node>> children_;

 public:
  [[nodiscard]]
  NodeType type() const noexcept override {
    return NodeType::Document;
  }

  /** 移动节点进入 Document */
  void append(std::unique_ptr<Node> child) {
    // 保证 Document 内部每个 unique_ptr 都有效
    if (!child) {
      throw std::invalid_argument{"Document child must not be null"};
    }
    children_.push_back(std::move(child));
  }

  [[nodiscard]]
  const std::vector<std::unique_ptr<Node>>& children() const noexcept {
    return children_;
  }
};
}  // namespace MiniEditor::parser
