add_library(minieditor_lexer STATIC
  Lexer.cpp)
add_library(MiniEditor::Lexer ALIAS minieditor_lexer)

target_sources(minieditor_lexer
  PRIVATE
    Lexer.h
    Token.h
    TokenType.h
)

# Lexer.h 和 Token.h 会被 Parser、应用和测试包含，所以使用 PUBLIC 路径
target_include_directories(minieditor_lexer
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_compile_features(minieditor_lexer
  PUBLIC
    cxx_std_20
)

minieditor_enable_warnings(minieditor_lexer)
minieditor_enable_sanitizers(minieditor_lexer)
