/**
 * @file lexer_basic_text.cpp
 * @author Alligator
 * @brief 测试词法分析器
 * @version 0.1
 * @date 2026-07-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <cassert>
#include <iostream>

#include "parser/lexer/Lexer.h"

namespace {
using mini::parser::Lexer;
using mini::parser::Token;
using mini::parser::TokenType;

/**
 * @brief 断言 Token 的属性是否符合预期
 */
void assertToken(const Token& token, TokenType expectedType,
                 const std::string_view expectedLexeme, size_t expectedLine,
                 size_t expectedCol) {
  bool typeMatch = token.type == expectedType;
  bool lexemeMatch = token.lexeme == expectedLexeme;
  bool lineMatch = token.line == expectedLine;
  bool colMatch = token.column == expectedCol;
  if (!typeMatch || !lexemeMatch || !lineMatch || !colMatch) {
    std::cerr << "Token assertion failed:\n";
    std::cerr << "Expected: Type=" << static_cast<int>(expectedType)
              << ", Lexeme=\"" << expectedLexeme << "\", Line=" << expectedLine
              << ", Column=" << expectedCol << "\n";
    std::cerr << "Actual: Type=" << static_cast<int>(token.type)
              << ", Lexeme=\"" << token.lexeme << "\", Line=" << token.line
              << ", Column=" << token.column << "\n";
  }
  assert(typeMatch);
  assert(lexemeMatch);
  assert(lineMatch);
  assert(colMatch);
}

void testLexerBasicText() {
  std::string input = "# Hello\nThis is a test.\n# Another Heading";
  Lexer lexer(input);
  auto tokens = lexer.tokenize();

  // 断言 Token 数量
  assert(tokens.size() == 8);

  // 断言每个 Token 的属性
  assertToken(tokens[0], TokenType::Hash, "#", 1, 1);
  assertToken(tokens[1], TokenType::Text, " Hello", 1, 2);
  assertToken(tokens[2], TokenType::NewLine, "\n", 1, 8);
  assertToken(tokens[3], TokenType::Text, "This is a test.", 2, 1);
  assertToken(tokens[4], TokenType::NewLine, "\n", 2, 16);
  assertToken(tokens[5], TokenType::Hash, "#", 3, 1);
  assertToken(tokens[6], TokenType::Text, " Another Heading", 3, 2);
  assertToken(tokens[7], TokenType::EndOfFile, "", 3, 18);
  std::cout << "All lexer basic text tests passed successfully! 🎉\n";
}

void testLexerEmptyInput() {
  std::string input = "";
  Lexer lexer(input);
  auto tokens = lexer.tokenize();

  // 断言 Token 数量
  assert(tokens.size() == 1);

  // 断言唯一的 Token 是 EndOfFile
  assertToken(tokens[0], TokenType::EndOfFile, "", 1, 1);

  std::cout << "Lexer empty input test passed successfully! 🎉\n";
}

void testHeadingMark() {
  std::string input = "### Heading Level 3";
  Lexer lexer(input);
  auto tokens = lexer.tokenize();

  // 断言 Token 数量
  assert(tokens.size() == 3);

  // 断言每个 Token 的属性
  assertToken(tokens[0], TokenType::Hash, "###", 1, 1);
  assertToken(tokens[1], TokenType::Text, " Heading Level 3", 1, 4);
  assertToken(tokens[2], TokenType::EndOfFile, "", 1, 20);

  std::cout << "Heading mark token test passed successfully! 🎉\n";
}

void testMultiLine() {
  std::string input = "# Heading 1\nSome text here.\n## Heading 2\nMore text.";
  Lexer lexer(input);
  auto tokens = lexer.tokenize();

  // 断言 Token 数量
  assert(tokens.size() == 10);

  // 断言每个 Token 的属性
  assertToken(tokens[0], TokenType::Hash, "#", 1, 1);
  assertToken(tokens[1], TokenType::Text, " Heading 1", 1, 2);
  assertToken(tokens[2], TokenType::NewLine, "\n", 1, 12);
  assertToken(tokens[3], TokenType::Text, "Some text here.", 2, 1);
  assertToken(tokens[4], TokenType::NewLine, "\n", 2, 16);
  assertToken(tokens[5], TokenType::Hash, "##", 3, 1);
  assertToken(tokens[6], TokenType::Text, " Heading 2", 3, 3);
  assertToken(tokens[7], TokenType::NewLine, "\n", 3, 13);
  assertToken(tokens[8], TokenType::Text, "More text.", 4, 1);
  assertToken(tokens[9], TokenType::EndOfFile, "", 4, 11);
  std::cout << "Multi-line token test passed successfully! 🎉\n";
}
}  // namespace

int main() {
  testLexerBasicText();
  testLexerEmptyInput();
  testHeadingMark();
  testMultiLine();

  std::cout << "✅ All lexer tests passed successfully! 🎉\n";
  return 0;
}
