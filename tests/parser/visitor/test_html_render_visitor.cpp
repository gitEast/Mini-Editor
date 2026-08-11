#include <cassert>

#include "parser/ast/HeadingNode.h"
#include "parser/ast/ParagraphNode.h"
#include "parser/lexer/Lexer.h"
#include "parser/parser/Parser.h"
#include "parser/visitor/HtmlRenderVisitor.h"

namespace {
using MiniEditor::parser::DocumentNode;
using MiniEditor::parser::HeadingNode;
using MiniEditor::parser::HtmlRenderVisitor;
using MiniEditor::parser::Lexer;
using MiniEditor::parser::ParagraphNode;
using MiniEditor::parser::Parser;

void testRenderEmptyDocument() {
  DocumentNode document;
  HtmlRenderVisitor renderer;

  document.accept(renderer);

  assert(renderer.result().empty());
}

void testRenderHandmadeAst() {
  DocumentNode document;
  document.append(std::make_unique<HeadingNode>(2, "Visitor"));
  document.append(std::make_unique<ParagraphNode>("Render an AST as HTML."));

  HtmlRenderVisitor renderer;
  document.accept(renderer);

  const std::string expected =
      "<h2>Visitor</h2>\n"
      "<p>Render an AST as HTML.</p>\n";
  assert(renderer.result() == expected);
}

void testEscapeHtml() {
  DocumentNode document;
  document.append(std::make_unique<ParagraphNode>("<tag> & \"quoted\" 'text'"));

  HtmlRenderVisitor renderer;
  document.accept(renderer);
  assert(renderer.result() ==
         "<p>&lt;tag&gt; &amp; &quot;quoted&quot; &#39;text&#39;</p>\n");
}

void testResetRenderer() {
  DocumentNode firstDocument;
  firstDocument.append(std::make_unique<HeadingNode>(1, "First"));

  DocumentNode secondDocument;
  secondDocument.append(std::make_unique<ParagraphNode>("Second"));

  HtmlRenderVisitor renderer;
  firstDocument.accept(renderer);
  assert(renderer.result() == "<h1>First</h1>\n");

  renderer.reset();
  secondDocument.accept(renderer);
  assert(renderer.result() == "<p>Second</p>\n");
}

void testMarkdownToHtmlPipeline() {
  const std::string source =
      "# MiniEditor\n"
      "\n"
      "A small Markdown editor.";
  Lexer lexer{source};
  Parser parser(lexer.tokenize());
  const DocumentNode document = parser.parse();

  HtmlRenderVisitor renderer;
  document.accept(renderer);

  const std::string expected =
      "<h1>MiniEditor</h1>\n"
      "<p>A small Markdown editor.</p>\n";
  assert(renderer.result() == expected);
}
}  // namespace

int main() {
  testRenderEmptyDocument();
  testRenderHandmadeAst();
  testEscapeHtml();
  testResetRenderer();
  testMarkdownToHtmlPipeline();
  return 0;
}
