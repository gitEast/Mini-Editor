#include "parser/lexer/Lexer.h"

#include <cassert>
#include <cctype>

Lexer::Lexer(const std::string_view source) : source_(source) {}

/* ------------ ⬇ Lexer 状态机 ⬇ ------------ */
std::vector<Token> Lexer::tokenize() {
  // 1. 初始化（目的：每次调用都得到相同结果）
  tokens_.clear();
  start_ = 0;
  current_ = 0;
  line_ = 1;
  column_ = 1;
  tokenLine_ = 1;
  tokenColumn_ = 1;
  // 2. 循环读取 Token：每次一个
  while (!isAtEnd()) {
    // 2.1 保存 Token 的起点
    start_ = current_;
    tokenLine_ = line_;
    tokenColumn_ = column_;
    // 2.2 扫描并生成 Token
    scanToken();
  }
  // 3. 标识解析结束，并返回结果
  emitEndOfFile();  // ‼️ 结束标识
  return tokens_;
}
void Lexer::scanToken() {
  switch (peek()) {
    case '#':  // hash
      advance();
      emitToken(TokenType::Hash);
      break;
    case '\n':  // New Line
      advance();
      emitToken(TokenType::NewLine);
      break;
    default:  // 普通字符
      readText();
      break;
  }
}
void Lexer::readText() {
  while (!isAtEnd()) {
    const char c = peek();
    if (c == '#' || c == '\n') break;
    advance();
  }
  emitToken(TokenType::Text);
}
/* ------------ ⬆ Lexer 状态机 ⬆ ------------ */

/* ------------ ⬇ 位置相关 ⬇ ------------ */
bool Lexer::isAtEnd() const noexcept { return current_ >= source_.size(); }
char Lexer::peek() const noexcept {
  if (isAtEnd()) return '\0';  // 返回空字符表示结束
  return source_[current_];
}
/** 消费一个字符：位置信息的唯一修改入口 */
char Lexer::advance() noexcept {
  // 前提：保证一定有字符未解析
  assert(!isAtEnd());
  // 1. 消费字符
  const char c = source_[current_++];
  // 2. 维护当前 cursor 的位置信息
  if (c == '\n') {
    line_++;
    column_ = 1;
  } else {
    column_++;
  }
  // 3. 返回需要消费的字符
  return c;
}
/* ------------ ⬆ 位置相关 ⬆ ------------ */

/* ------------ ⬇ 生成 Token ⬇ ------------ */
void Lexer::emitToken(TokenType type) {
  std::string_view lexeme = source_.substr(start_, current_ - start_);
  tokens_.emplace_back(type, lexeme, tokenLine_, tokenColumn_);
}
void Lexer::emitEndOfFile() {
  tokens_.emplace_back(TokenType::EndOfFile, "", line_, column_);
}
/* ------------ ⬆ 生成 Token ⬆ ------------ */
