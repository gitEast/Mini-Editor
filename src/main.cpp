#include <iostream>
#include <string>
#include <string_view>

#include "parser/ast/HeadingNode.h"
#include "parser/ast/ParagraphNode.h"
#include "parser/lexer/Lexer.h"
#include "parser/parser/Parser.h"

namespace {
using mini::parser::DocumentNode;
using mini::parser::HeadingNode;
using mini::parser::Node;
using mini::parser::NodeType;
using mini::parser::ParagraphNode;

void printDocument(const DocumentNode& document) {
  std::cout << "Document\n";
  for (const auto& child : document.children()) {
    const Node& node = *child;
    switch (node.type()) {
      case NodeType::Heading: {
        // node 的实际类型由上面的 type() 判定为 HeadingNode；
        // static_cast 将 Node 基类引用向下转换为 HeadingNode
        // 引用，以访问标题层级和文本。
        const auto& heading = static_cast<const HeadingNode&>(node);
        std::cout << "   Heading(level=" << heading.level() << ")\n"
                  << "    Text(\"" << heading.text().text() << "\")\n";
        break;
      }
      case NodeType::Paragraph: {
        const auto& paragraph = static_cast<const ParagraphNode&>(node);
        std::cout << "   Paragraph\n"
                  << "     Text(\"" << paragraph.text().text() << "\")\n";
        break;
      }
      case NodeType::Document:  // case 后没有语句和 break，会继续执行下一个
                                // case（贯穿）。
      case NodeType::Text:      // 两种节点共用下面的 break，本函数不输出它们。
        break;
      default:
        break;
    }
  }
}
}  // namespace

int main() {
  const std::string source =
      "# MiniDocs\n"
      "\n"
      "A small Markdown editor.\n"
      "Built with C++20.\n"
      "\n"
      "## Goals\n"
      "Learn C++ through practice.";

  mini::parser::Lexer lexer{source};
  auto tokens = lexer.tokenize();

  mini::parser::Parser parser{std::move(tokens)};
  const auto document = parser.parse();

  printDocument(document);

  return 0;
}
