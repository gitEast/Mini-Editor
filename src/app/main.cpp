#include <iostream>
#include <string>
#include <string_view>

#include "parser/lexer/Lexer.h"
#include "parser/parser/Parser.h"
#include "parser/visitor/HtmlRenderVisitor.h"

int main() {
  const std::string source =
      "# MiniDocs\n"
      "\n"
      "A small Markdown editor.\n"
      "Built with C++20.\n"
      "\n"
      "## Goals\n"
      "Learn C++ through practice.";

  MiniEditor::parser::Lexer lexer{source};
  auto tokens = lexer.tokenize();

  MiniEditor::parser::Parser parser{std::move(tokens)};
  const auto document = parser.parse();

  MiniEditor::parser::HtmlRenderVisitor renderer;
  document.accept(renderer);

  std::cout << renderer.result();

  return 0;
}
