/**
 * @file Parser.h
 * @author Alligator
 * @brief 将 Tokens 构造成为 AST 树
 * @version 0.1
 * @date 2026-08-06
 * @copyright Copyright (c) 2026
 */
#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "parser/ast/DocumentNode.h"
#include "parser/ast/Node.h"
#include "parser/lexer/Token.h"

namespace mini::parser {
class Parser {
 public:
  explicit Parser(std::vector<Token> tokens);

  [[nodiscard]]
  DocumentNode parse();

 private:
  [[nodiscard]]
  bool isAtEnd() const noexcept;

  [[nodiscard]]
  const Token& peek(size_t offset = 0) const noexcept;

  [[nodiscard]]
  bool check(TokenType type, size_t offset = 0) const noexcept;

  const Token& advance() noexcept;

  void skipBlankLines() noexcept;

  [[nodiscard]]
  bool isHeadingStart() const noexcept;

  [[nodiscard]]
  std::unique_ptr<Node> parseHeading();

  [[nodiscard]]
  std::unique_ptr<Node> parseParagraph();

  std::vector<Token> tokens_;
  size_t current_ = 0;
};

}  // namespace mini::parser
