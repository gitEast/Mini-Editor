#include <iostream>
#include <string>
#include <string_view>

#include "parser/lexer/Lexer.h"

void printToken(const Token& token);
std::string_view tokenTypeName(TokenType token);
std::string_view escapedLexeme(const Token& token);

int main() {
  const std::string app_name = "Mini Editor";
  std::cout << "Welcome to " << app_name << " (C++20 Mode)" << std::endl;
  std::cout << "-----------------------------------" << std::endl;

  const std::string source = "# Hello\n\nWorld";
  Lexer lexer(source);
  const auto tokens = lexer.tokenize();
  for (const auto& token : tokens) {
    printToken(token);
  }
}

void printToken(const Token& token) {
  std::cout << tokenTypeName(token.type) << "(\"" << escapedLexeme(token)
            << "\", line=" << token.line << ", column=" << token.column
            << ")\n";
}
std::string_view tokenTypeName(TokenType type) {
  switch (type) {
    case TokenType::Hash:
      return "Hash";
    case TokenType::NewLine:
      return "NewLine";
    case TokenType::Text:
      return "Text";
    case TokenType::EndOfFile:
      return "EndOfFile";
    default:
      return "Unknown";
  }
}
std::string_view escapedLexeme(const Token& token) {
  switch (token.type) {
    case TokenType::Hash:
      return "#";
    case TokenType::NewLine:
      return "\\n";  // 输出 '\n'，否则打印时真的换行，难以辨认
    case TokenType::Text:
    case TokenType::EndOfFile:
      return token.lexeme;
    default:
      return "Unknown";
  }
}
