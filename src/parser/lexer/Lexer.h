/**
 * @file Lexer.h
 * @author Alligator
 * @brief 词法分析器
 * @version 0.1
 * @date 2026-07-2
 * @copyright Copyright (c) 2026
 */
#pragma once
#include <string_view>
#include <vector>

#include "Token.h"

class Lexer {
 public:
  explicit Lexer(const std::string_view source);  // 传入要解析的 Markdown 文本
  [[nodiscard]]
  std::vector<Token> tokenize();  // 主入口：将文本一次性切成 Token 数组

 private:
  [[nodiscard]]
  bool isAtEnd() const noexcept;  // 判断是否读取到了字符串末尾 🔚
  [[nodiscard]]
  char peek() const noexcept;  // 查看当前指针指向的字符
  char advance() noexcept;  // 消费并返回当前字符（指针前进1位，并更新行列号）

  void scanToken();  // 扫描一个
                     // Token（根据当前字符判断类型，并调用对应的子状态函数）
  void readText();   // 子状态：读取一段普通文本
  void emitToken(TokenType type);
  void emitEndOfFile();

  std::string_view source_;     // 保存本次扫描的完整输入
  std::vector<Token> tokens_;  // 保存解析出的 Token 数组

  size_t start_ = 0;
  size_t current_ = 0;
  
  size_t line_ = 1;
  size_t column_ = 1;
  size_t tokenLine_ = 1;
  size_t tokenColumn_ = 1;
};
