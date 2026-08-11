#include "parser/visitor/HtmlRenderVisitor.h"

#include "parser/ast/DocumentNode.h"
#include "parser/ast/HeadingNode.h"
#include "parser/ast/ParagraphNode.h"
#include "parser/ast/TextNode.h"

namespace MiniEditor::parser {
void HtmlRenderVisitor::visit(const DocumentNode& node) {
  for (const auto& child : node.children()) {
    child->accept(*this);
  }
}
void HtmlRenderVisitor::visit(const HeadingNode& node) {
  const std::string tag = "h" + std::to_string(node.level());

  output_ += "<" + tag + ">";
  node.text().accept(*this);
  output_ += "</" + tag + ">";
  output_ += "\n";
}
void HtmlRenderVisitor::visit(const ParagraphNode& node) {
  output_ += "<p>";
  node.text().accept(*this);
  output_ += "</p>";
  output_ += "\n";
}
void HtmlRenderVisitor::visit(const TextNode& node) {
  output_ += escapeHtml(node.text());
}

const std::string& HtmlRenderVisitor::result() const noexcept {
  return output_;
}

void HtmlRenderVisitor::reset() noexcept { output_.clear(); }

std::string HtmlRenderVisitor::escapeHtml(const std::string& text) {
  std::string escaped;
  escaped.reserve(text.size());

  /* 专门针对 HTML 的转义 */
  for (const char character : text) {
    switch (character) {
      case '&':
        escaped += "&amp;";
        break;
      case '<':
        escaped += "&lt;";
        break;
      case '>':
        escaped += "&gt;";
        break;
      case '"':
        escaped += "&quot;";
        break;
      case '\'':
        escaped += "&#39;";
        break;
      default:
        escaped += character;
        break;
    }
  }

  return escaped;
}
}  // namespace MiniEditor::parser
