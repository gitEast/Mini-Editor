/**
 * @file NodeType.h
 * @author Alligator
 * @brief AST 节点类型枚举
 * @version 0.1
 * @date 2026-07-28
 * @copyright Copyright (c) 2026
 */
enum class NodeType {
  Document,   // 文档节点，只做容器使用
  Heading,    // 标题节点
  Paragraph,  // 段落节点，也是容器节点
  Text        // 文本节点
};