/**
 * @file Node.h
 * @author Alligator
 * @brief AST 节点抽象基类
 * @version 0.1
 * @date 2026-07-28
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "parser/visitor/Visitor.h"

namespace MiniEditor::parser {
/** 节点枚举类型 */
enum class NodeType { Document, Heading, Paragraph, Text };

class Node {
 public:
  virtual ~Node() = default;

  [[nodiscard]]
  virtual NodeType type() const noexcept = 0;  // 提供统一接口，纯虚函数

  virtual void accept(Visitor& visitor) const = 0;
};
}  // namespace MiniEditor::parser
