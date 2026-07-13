# C++ Markdown 编辑器项目方案

## 一、项目定位

项目名称：

Mini Markdown Editor（暂定）

目标：

使用 C++20 构建一个现代 Markdown 编辑器，通过真实项目提升 C++ 工程能力。

最终目标：

- Markdown 编辑
- 实时预览
- HTML/CSS 渲染
- 文件管理
- 双向链接
- 插件系统
- AI 辅助能力

学习目标：

- C++20 工程开发
- CMake 构建体系
- 面向对象设计
- AST 与 Parser 设计
- GUI 开发
- 软件架构设计
- 插件系统设计

## 二、核心架构设计

### 总体流程

正确的数据流：

    Markdown文本
          |
          v
    Lexer（词法分析）
          |
          v
    Parser（语法分析）
          |
          v
    AST（抽象语法树）
          |
          v
    Renderer（渲染器）
          |
          +---- HTML Renderer
          |
          +---- Qt Renderer
          |
          +---- PDF Renderer

核心原则：

AST 是核心中间表示，HTML 只是输出形式之一。

## 三、软件模块设计

### 1. Application 层

职责：

管理应用生命周期。

模块：

    Application

    ├── main()
    ├── ConfigManager
    ├── PluginManager
    └── EventBus

功能：

- 程序启动
- 配置加载
- 插件初始化
- 全局事件通信

### 2. UI 层

技术：

Qt6

模块：

    ui

    ├── MainWindow
    ├── EditorView
    ├── PreviewView
    ├── FileExplorer
    └── SettingPanel

功能：

- 窗口管理
- 编辑区域
- 文件浏览
- 设置界面

### 3. Core 层

核心业务模型：

    core

    ├── Document
    ├── Editor
    ├── Command
    └── History

负责：

- 文档状态
- 编辑操作
- Undo/Redo
- 数据管理

### 4. Markdown Parser 层

这是项目核心学习模块。

流程：

    Markdown

    ↓

    Lexer

    ↓

    Parser

    ↓

    AST

AST 示例：

Markdown：

```markdown
# Hello

This is **bold**
```

生成：

    Document

    ├── Heading(level=1)
    │      |
    │      Text("Hello")
    │
    └── Paragraph
           |
           ├── Text("This is ")
           |
           └── Bold
                  |
                  Text("bold")

目录：

    parser

    ├── Lexer
    ├── Parser
    ├── AST
    │
    ├── Node
    │   ├── DocumentNode
    │   ├── HeadingNode
    │   ├── ParagraphNode
    │   ├── TextNode
    │   └── BoldNode
    │
    └── Visitor

### 5. Renderer 层

负责 AST 到最终显示。

结构：

    renderer

    ├── HtmlRenderer
    ├── QtRenderer
    ├── PdfRenderer
    └── ThemeManager

例如：

AST：

    HeadingNode

HTML Renderer：

```html
<h1>Hello</h1>
```

Qt Renderer：

生成 Qt 显示对象。

### 6. Storage 层

负责文件和数据管理。

    storage

    ├── FileManager
    ├── Workspace
    ├── Metadata
    └── Database

功能：

- Markdown 文件读取
- 保存
- 工作空间
- 索引

### 7. Plugin 系统

目标：

支持扩展。

结构：

    plugins

    ├── PluginInterface
    ├── PluginLoader
    └── PluginManager

学习：

- 动态库
- ABI
- 接口设计

### 8. AI 模块（后期）

结构：

    AI

    ├── Embedding
    ├── VectorStore
    ├── RAG
    └── Assistant

功能：

- 文档搜索
- 自动总结
- AI 问答

## 四、开发阶段规划

### Phase 1：Markdown 核心引擎

周期：

1-2个月

目标：

实现：

    Markdown

    ↓

    AST

    ↓

    HTML

学习：

- Parser
- 数据结构
- C++设计

### Phase 2：Qt 编辑器

周期：

2-3个月

实现：

- 编辑窗口
- 文件打开
- 保存
- 实时预览

### Phase 3：现代编辑器能力

实现：

- 搜索
- 快捷键
- 主题
- 双链
- 标签系统

### Phase 4：插件系统

实现：

- 动态插件加载
- 插件 API
- 扩展机制

### Phase 5：AI能力

实现：

- 本地知识库
- RAG
- AI助手

## 五、第一个月详细计划

目标：

完成一个命令行 Markdown 引擎。

最终效果：

输入：

    test.md

内容：

```markdown
# Hello

This is **Markdown**
```

输出：

```html
<h1>Hello</h1>
<p>
  This is
  <strong>Markdown</strong>
</p>
```

### Week 1：C++工程基础

#### 1.1 目标

学习：

- C++20 基础
- CMake
- Git
- 单元测试

项目结构：

    MiniEditor
    ├── CMakeLists.txt
    ├── src
    ├── include
    ├── tests
    └── README.md

完成：

- 编译环境
- 调试
- 测试框架

#### 1.2 具体实现

1. 环境配置
   1. 编译器`$ clang++ --version`
      - Apple clang version 21.0.0 (clang-2100.0.123.102)
      - Target: arm64-apple-darwin25.5.0
      - Thread model: posix
      - InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
   2. 构建工具：CMake `$ brew install cmake`
   3. vs code 插件
      - `C/C++`: 提供语法高亮、代码提示
      - `CMake Tools`: 负责一键编译、运行、调试

### Week 2：AST设计

目标：

建立 Markdown 数据模型。

实现：

    Node
    ├── DocumentNode
    ├── HeadingNode
    ├── ParagraphNode
    ├── TextNode
    └── BoldNode

掌握：

- 类设计
- 继承
- 多态
- 智能指针

### Week 3：Parser实现

支持语法：

标题：`# title`

粗体：`**text**`

段落：`hello world`

流程：

    Markdown

    ↓

    Lexer

    ↓

    Parser

    ↓

    AST

### Week 4：Renderer实现

实现：

    AST

    ↓

    HtmlRenderer

    ↓

    HTML

增加：

- 单元测试
- 错误处理
- 文档

## 六、第一个月验收标准

功能：

- Markdown 文件读取
- AST生成
- HTML输出
- 基础语法支持

技术能力：

掌握：

- C++类设计
- RAII
- 智能指针
- CMake
- Parser设计
- 单元测试

最终项目结构：

    MiniEditor

    ├── core
    ├── parser
    ├── renderer
    ├── storage
    ├── tests
    └── app

## 七、长期成长路线

C++基础

↓

数据结构

↓

Parser设计

↓

AST设计

↓

GUI开发

↓

系统架构

↓

插件系统

↓

AI应用
