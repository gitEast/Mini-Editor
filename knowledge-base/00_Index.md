# 索引与学习路线路线图（核心！）

## 具体目录

### Week 01

[C++ 智能指针（Smart Pointers）](./lang_smart_pointers.md)
[面向对象与多态（Virtual & Override）](./lang_oop_virtual_override.md)
[std::string_view（C++现代语法）](./lang_string_view.md)

## 命名逻辑

```
cpp-core/  (或你的知识库根目录)
├── 00_Index.md                   # 索引与学习路线路线图（核心！）
│
├── lang_string_view.md           # C++ 特性 string_view
├── lang_smart_pointers.md        # 智能指针 (shared_ptr/unique_ptr)
├── lang_oop_virtual_override.md  # 面向对象与多态 (virtual/override)
│
├── ast_concepts.md               # 编译器/AST 相关理论
├── ast_nodes_design.md           # AST 节点设计与实现
│
└── arch_memory_management.md     # 架构与内存管理通用思考
```

1. 00_Index.md：这是你的“仪表盘”。不要一上来就写单点知识，在这个文件里写下你的 Week 2 学习目标。把各个拆分的文档做成内链（Apple Notes 支持 [[ 链接其他笔记，Markdown 也支持相对路径）。
2. `lang_` 前缀（Language 核心语言特性）：
   - 将智能指针、虚函数、std::string_view 归为此类。
   - 优势：当你打出 `lang_` 时，所有关于 C++ 语法的硬核知识点会全部对齐排在一起。
3. `ast_` 前缀（Abstract Syntax Tree 专栏项目）：
   - 用来记录你把这些 C++ 基础应用到 AST 构建时的设计笔记。
   - 例如：在 `ast_nodes_design.md` 里，你会记录“为什么 AST 子节点要用 `std::unique_ptr` 而不是 `std::shared_ptr`（因为语法树是严格的单所有权树状结构）”。

## 笔记模板

```markdown
# 🏷️ Topic: C++ 智能指针 (Smart Pointers)

## 🫯 为什么会有这个东西（Pain Point）

## 💡 核心思想（Design Philosophy）

## 🛠 实现原理（Under the Hood）

## 🧩 常用 API（How to Use）

## ⚠️ 工程避坑（Pitfalls）

## 🚀 项目中的应用（Project Practice）

## 🎯 总结（Takeaway）
```
