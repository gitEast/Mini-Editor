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

namespace mini::parser {
struct Token {
  TokenType type;           // 类型
  std::string_view lexeme;  // 文本
  /** 起始位置信息 */
  size_t line{1};    // 该 token 所在源码的行号，1-based
  size_t column{1};  // 该 token 所在源码的列号，1-based
};
}  // namespace mini::parser
