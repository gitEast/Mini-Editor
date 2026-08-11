#pragma once

#include <string>

#include "parser/visitor/Visitor.h"

namespace MiniEditor::parser {
class HtmlRenderVisitor final : public Visitor {
 public:
  void visit(const DocumentNode& node) override;
  /** "# 标题" => "<h1>标题</h1>" */
  void visit(const HeadingNode& node) override;
  void visit(const ParagraphNode& node) override;
  void visit(const TextNode& node) override;

  [[nodiscard]]
  const std::string& result() const noexcept;

  void reset() noexcept;

 private:
  static std::string escapeHtml(const std::string& text);

  std::string output_;  // 保留一次渲染过程的结果
};

}  // namespace MiniEditor::parser
