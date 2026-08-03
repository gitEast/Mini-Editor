/**
 * @file Node.h
 * @author Alligator
 * @brief AST 节点抽象基类
 * @version 0.1
 * @date 2026-07-28
 * @copyright Copyright (c) 2026
 */
#include "NodeType.h"

class Node {
 public:
  virtual ~Node() = default;
  virtual NodeType getType() const = 0;
};
