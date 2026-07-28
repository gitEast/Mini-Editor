#include "Lexer.h"

#include <cctype>

Lexer::Lexer(const std::string_view input) : input(input) {}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  while (!isAtEnd()) {
    char c = peek();
    if (c == '#')
      tokens.push_back(readHeadingMark());  // 读取标题标记
    else if (c == '\n')
      tokens.push_back(readNewLine());  // 读取换行符
    else
      tokens.push_back(readText());  // 读取普通文本
  }
  tokens.emplace_back(
      Token{TokenType::EndOfFile, "", line, column});  // 添加文件结束标记
  return tokens;
}

char Lexer::peek() const {
  if (isAtEnd()) return '\0';  // 返回空字符表示结束
  return input[currentIndex];
}
char Lexer::advance() {
  char c = input[currentIndex++];
  if (c == '\n') {
    line++;
    column = 1;
  } else {
    column++;
  }
  return c;
}
bool Lexer::isAtEnd() const { return currentIndex >= input.size(); }

Token Lexer::readHeadingMark() {
  size_t startLine = line;
  size_t startCol = column;
  size_t start = currentIndex;
  // 读取连续的 #
  while (peek() == '#') advance();
  return Token(TokenType::HeadingMark,
               input.substr(start, currentIndex - start), startLine, startCol);
}
Token Lexer::readNewLine() {
  size_t startLine = line;
  size_t startCol = column;
  size_t start = currentIndex;
  advance();  // 消费换行符
  return Token(TokenType::NewLine, input.substr(start, 1), startLine, startCol);
}
Token Lexer::readText() {
  size_t startLine = line;
  size_t startCol = column;
  size_t start = currentIndex;
  // 遇到 special 字符（# 或 \n）就停止读取普通文
  while (!isAtEnd() && peek() != '#' && peek() != '\n') {
    advance();
  }
  return Token(TokenType::Text, input.substr(start, currentIndex - start),
               startLine, startCol);
}
