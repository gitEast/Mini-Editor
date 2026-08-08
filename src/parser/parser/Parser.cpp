#include "parser/parser/Parser.h"

#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include "parser/ast/HeadingNode.h"
#include "parser/ast/ParagraphNode.h"

namespace mini::parser {
/** 输入契约：只要存在且仅在末尾存在一个 EndOfFile Token */
Parser::Parser(std::vector<Token> tokens) : tokens_(std::move(tokens)) {
  if (tokens_.empty()) {
    throw std::invalid_argument{"Parser requires a non-empty token stream"};
  }

  if (tokens_.back().type != TokenType::EndOfFile) {
    throw std::invalid_argument{"Token stream must end with EndOfFile"};
  }

  for (size_t i = 0; i + 1 < tokens_.size(); ++i) {
    if (tokens_[i].type == TokenType::EndOfFile) {
      throw std::invalid_argument{"EndOfFile must appear only at the end"};
    }
  }
}

DocumentNode Parser::parse() {
  current_ = 0;
  DocumentNode document;

  while (!isAtEnd()) {
    skipBlankLines();

    if (isAtEnd()) break;
    if (isHeadingStart())
      document.append(parseHeading());
    else
      document.append(parseParagraph());
  }

  return document;
}

bool Parser::isAtEnd() const noexcept {
  return peek().type == TokenType::EndOfFile;
}

/**
 * @brief 查看未消费的 tokens
 * @param offset 允许检查多个 Token
 * @return const Token&
 */
const Token& Parser::peek(size_t offset) const noexcept {
  const size_t lastIndex = tokens_.size() - 1;
  const size_t remaining = lastIndex - current_;

  // 请求超出末尾时，返回 EOF Token
  if (offset > remaining) return tokens_.back();
  return tokens_[current_ + offset];
}

bool Parser::check(TokenType type, size_t offset) const noexcept {
  return peek(offset).type == type;
}

const Token& Parser::advance() noexcept {
  const Token& token = peek();
  /** 已经到结束标识时，不再增加 current_，避免超过最后索引 */
  if (!isAtEnd()) current_++;
  return token;
}

void Parser::skipBlankLines() noexcept {
  while (check(TokenType::NewLine)) {
    advance();
  }
}

/** HeadingStart 要求：1. 以 #{1,6} 开头；2. 紧随其后的是空格 + 普通文本 */
bool Parser::isHeadingStart() const noexcept {
  // 保证 以 # 开头
  if (!check(TokenType::Hash) || peek().column != 1) return false;

  size_t offset = 0;
  size_t level = 0;

  /* 统计等级 */
  while (check(TokenType::Hash, offset)) {
    level++;
    offset++;
  }
  // 保证标题等级: #{1,6}
  if (level < 1 || level > 6) return false;
  // 保证 #{1,6} 后紧跟的是 Text
  if (!check(TokenType::Text, offset)) return false;
  const std::string_view text = peek(offset).lexeme;
  // 保证 Text 有内容，且以空格开头
  return !text.empty() && text.front() == ' ';
}

/** 构造标题 */
std::unique_ptr<Node> Parser::parseHeading() {
  // 1. 确定标题等级
  size_t level = 0;
  while (check(TokenType::Hash)) {
    advance();
    level++;
  }
  const Token& firstText = advance();
  // 2. 构造标题内容
  // 2.1 删除第一个语法空格
  std::string text = std::string{firstText.lexeme.substr(1)};
  // 2.2 连接本行剩余 Token
  while (!isAtEnd() && !check(TokenType::NewLine)) {
    text += advance().lexeme;
  }
  // 3. 消费本行最后的换行符（如果有的话）
  if (check(TokenType::NewLine)) advance();
  return std::make_unique<HeadingNode>(level, std::move(text));
}

/** 构造段落：段落内允许出现一个换行符 */
std::unique_ptr<Node> Parser::parseParagraph() {
  std::string text;

  // 处理多行
  while (!isAtEnd()) {
    // 处理当前行
    while (!isAtEnd() && !check(TokenType::NewLine)) {
      text += advance().lexeme;
    }
    if (isAtEnd()) break;
    // 消费一个换行符
    advance();
    // 段落结束标识：EOF || 第二个换行符 || 标题
    if (isAtEnd() || check(TokenType::NewLine) || isHeadingStart()) break;
    // 增加软换行：对上述消费的补偿
    text += '\n';
  }

  return std::make_unique<ParagraphNode>(std::move(text));
}
}  // namespace mini::parser
