# 声明 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.15)

# 定义项目名称、版本和语言
project(MiniEditor VERSION 1.0.0 LANGUAGES CXX)

# 强制要求使用 C+20 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 将 include 目录加入全局头文件搜索路径（类似于 alias 别名 path）
include_directories(include)

# 创建最终的可执行文件目标，并指定入口远嘛
add_executable(MiniEditor src/main.cpp)