add_library(minieditor_ast INTERFACE)
add_library(MiniEditor::AST ALIAS minieditor_ast)

target_sources(minieditor_ast
  INTERFACE
    Node.h
    TextNode.h
    HeadingNode.h
    ParagraphNode.h
    DocumentNode.h
)

# 保证 #include 时，不需要写 src
target_include_directories(minieditor_ast
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_compile_features(minieditor_ast
  INTERFACE
    cxx_std_20
)

