add_executable(minieditor_lexer_tests
  parser/lexer/test_lexer.cpp
)
# 测试只链接被测试模块
target_link_libraries(minieditor_lexer_tests
  PRIVATE
    MiniEditor::Lexer
)

target_compile_features(minieditor_lexer_tests
  PRIVATE
    cxx_std_20
)

minieditor_enable_warnings(minieditor_lexer_tests)
minieditor_enable_sanitizers(minieditor_lexer_tests)

add_test(
  NAME minieditor.lexer
  COMMAND minieditor_lexer_tests
)

set_tests_properties(minieditor.lexer
  PROPERTIES
    LABELS "unit;lexer"
)

##############################################

add_executable(minieditor_html_renderer_tests
  parser/visitor/test_html_render_visitor.cpp
)

target_link_libraries(minieditor_html_renderer_tests
  PRIVATE
    MiniEditor::HtmlRenderer
    MiniEditor::Parser
    MiniEditor::Lexer
)

target_compile_features(minieditor_html_renderer_tests
  PRIVATE
    cxx_std_20
)

minieditor_enable_warnings(minieditor_html_renderer_tests)
minieditor_enable_sanitizers(minieditor_html_renderer_tests)

add_test(
  NAME minieditor.html_renderer
  COMMAND minieditor_html_renderer_tests
)

set_tests_properties(minieditor.html_renderer
  PROPERTIES
    LABELS "unit;visitor;renderer"
)
