# 声明 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.20)

# 定义项目名称、版本和语言
project(
  MiniEditor 
  VERSION 0.1.0 
  DESCRIPTION "A minimal Markdown editor built with C++20"
  LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(MiniEditorWarnings)
include(MiniEditorSanitizers)
# 启用 CTest 支持；定义 BUILD_TESTING option；默认允许构建测试
include(CTest) 

option(MINIEDITOR_BUILD_APP "Build the MiniEditor command-line demo" ON)
option(MINIEDITOR_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(MINIEDITOR_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorsSanitizer" OFF)

# 生产代码位于 src
add_subdirectory(src)

if (BUILD_TESTING)
  add_subdirectory(tests)
endif()
