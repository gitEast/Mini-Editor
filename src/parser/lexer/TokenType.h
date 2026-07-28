/**
 * @file TokenType.h
 * @author Alligator
 * @brief 词法单元类型枚举
 * @version 0.1
 * @date 2026-07-27
 * @copyright Copyright (c) 2026
 */
enum class TokenType {
  HeadingMark,  // #
  Text,         // 任意连续字符，包括空格
  NewLine,      // 换行符 \n
  EndOfFile     // 文件结束标记
};
