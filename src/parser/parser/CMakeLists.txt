add_library(minieditor_parser STATIC
  Parser.cpp
)
add_library(MiniEditor::Parser ALIAS minieditor_parser)

target_sources(minieditor_parser
  PRIVATE
    Parser.h
)
target_include_directories(minieditor_parser
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)
target_compile_features(minieditor_parser
  PUBLIC
    cxx_std_20
)
target_link_libraries(minieditor_parser
  PUBLIC
    MiniEditor::AST
    MiniEditor::Lexer
)

minieditor_enable_warnings(minieditor_parser)
minieditor_enable_sanitizers(minieditor_parser)
