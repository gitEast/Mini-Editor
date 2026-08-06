# AST

## 目的

Token => AST

## 设计实现

### Version 1.0

- AST
  - DocumentNode
    - HeadingNode
      1. 以 `#` 开始，最多有 6 个 `#`
      2. 紧跟一个 Text，其第一个字符是空格
      3. 结束标识是换行符
    - ParagraphNode
      1. 结束标识是两个换行符/EndOfFile
