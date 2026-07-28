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
  explicit Lexer(const std::string_view input);  // 传入要解析的 Markdown 文本
  std::vector<Token> tokenize();  // 主入口：将文本一次性切成 Token 数组
  

 private:
  char peek() const;     // 查看当前指针指向的字符
  char advance();        // 消费并返回当前字符（指针前进1位，并更新行列号）
  bool isAtEnd() const;  // 判断是否读取到了字符串末尾 🔚

  Token readHeadingMark();  // 子状态：读取一个标题标记 #
  Token readText();         // 子状态：读取一段普通文本
  Token readNewLine();      // 子状态：读取一个换行符 \n

  std::string_view input;   // 保存待解析的文本
  size_t currentIndex = 0;  // 当前索引
  size_t line = 1;          // 当前行号
  size_t column = 1;        // 当前列号
};
