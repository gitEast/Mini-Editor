# 声明 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.15)

# 定义项目名称、版本和语言
project(MiniEditor VERSION 1.0.0 LANGUAGES CXX)

# 强制要求使用 C+20 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 将 include 目录加入全局头文件搜索路径（类似于 alias 别名 path）
include_directories(include src src/parser src/parser/lexer)

# 把 src/parser 下的代码自动收集并打包成静态库 Parser
file(GLOB_RECURSE PARSER_SOURCES "src/parser/*.cpp")
add_library(Parser STATIC ${PARSER_SOURCES})

enable_testing()

# 创建最终的可执行文件目标，并指定入口源码
add_executable(MiniEditor src/main.cpp)
# 链接静态库
target_link_libraries(MiniEditor PRIVATE Parser)

# 测试程序可执行文件
add_executable(run_tests tests/test_main.cpp)

# 测试 Lexer 模块的专项测试
add_executable(test_lexer tests/parser/lexer/test_lexer.cpp)
target_link_libraries(test_lexer PRIVATE Parser)

add_test(NAME LexerTest COMMAND test_lexer)
