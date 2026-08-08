# CMake 配置说明

## 结构

### 总体结构

- `CMakeLists.txt`:项目、options、测试总开关
  - `src/CMakeLists.txt`: 生产模块和应用装配
    - `src/parser/CMakeLists.txt`: AST、Lexer、Parser 子模块顺序
      - 子模块 `CMakeLists.txt`: 定义单个 target
  - `tests/CMakeLists.txt`: 测试 executable 与 CTest
  - `cmake/*.cmake`: 可服用的构建函数

### Parser 模块

- `parser/` 整个解析模块
  - `parser/lexer/`: 词法分析组件
  - `parser/ast/`: AST 数据组件
  - `parser/parser/`: 语法分析组件
