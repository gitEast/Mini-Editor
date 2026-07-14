# 索引与学习路线路线图（核心！）

## 具体目录

## 命名逻辑

```
cpp-core/  (或你的知识库根目录)
├── 00_Index.md                   # 索引与学习路线路线图（核心！）
│
├── lang_cpp20_string_view.md     # C++20 特性
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

## 1. 核心概念与 Code 示例

- `std::unique_ptr`: 独占所有权，不可复制，只能 move。用于生命周期明确的局部或树形拓扑。
- `std::shared_ptr`: 引用计数所有权。会有运行时额外开销（原子操作计数）。

快速复现的最小代码片段

## 2. 避坑指南 / 内存模型 (Under the Hood)

- 为什么不用 raw pointer？（防止忘记 delete 导致内存泄漏）
- `std::shared_ptr` 的循环引用陷阱（会导致内存永远无法释放，需配合 `std::weak_ptr`）。

## 3. AST 项目应用场景 (Connect)

- 结论：AST 的 Parent-Child 关系中，Child 节点一律使用 `std::unique_ptr<ASTNode>`。
- 原因：语法树是严格的单向拓扑，没有循环引用，`unique_ptr` 零运行时开销，最符合语义。
```
