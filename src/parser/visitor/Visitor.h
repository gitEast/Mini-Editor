#pragma once

namespace MiniEditor::parser {
class DocumentNode;
class HeadingNode;
class ParagraphNode;
class TextNode;

class Visitor {
 public:
  virtual ~Visitor() = default;

  /** visit 渲染过程：只读取 AST，并不修改 */
  virtual void visit(const DocumentNode& node) = 0;
  virtual void visit(const HeadingNode& node) = 0;
  virtual void visit(const ParagraphNode& node) = 0;
  virtual void visit(const TextNode& node) = 0;
};

}  // namespace MiniEditor::parser
