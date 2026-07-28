/**
 * @file Token.h
 * @author Alligator
 * @brief 最小语法单元
 * @version 0.1
 * @date 2026-07-27
 * @copyright Copyright (c) 2026
 */
#pragma once
#include <string_view>

#include "TokenType.h"

struct Token {
  TokenType type;
  std::string_view lexeme;
  /** 位置信息 */
  size_t line{1};    // 该 token 所在源码的行号
  size_t column{1};  // 该 token 所在源码的列号

  // 构造函数
  Token(TokenType t, std::string_view lex, size_t l = 1, size_t col = 1)
      : type(t), lexeme(lex), line(l), column(col) {}
};
