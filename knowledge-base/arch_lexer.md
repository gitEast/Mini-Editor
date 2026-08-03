# 词法分析器

## 目的

1. all 字符 => Token
2. 记录 Token 在原始字符串中的位置信息

## 设计实现

### Version 1.0

- Token 类型
  - Hash `#`
  - New Line `\n`
  - 普通文本（包括空格）
  - End of File: sentinel 效果，只出现一次，永远是最后的那个 Token
- Token 的位置信息
  - 半开区间：`[startOffset, endOffset)` 包含起点，不包含终点
    - 长度 = endOffset - startOffset
    - 相邻范围可以拼接
    - 空范围 `[x, x)`
- 不考虑错误处理
