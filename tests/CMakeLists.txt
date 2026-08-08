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

# add_executable(minieditor_parser_tests
#     ParserTests.cpp
# )

# target_link_libraries(minieditor_parser_tests
#     PRIVATE
#         MiniEditor::Parser
# )

# target_compile_features(minieditor_parser_tests
#     PRIVATE
#         cxx_std_20
# )

# minieditor_enable_warnings(minieditor_parser_tests)
# minieditor_enable_sanitizers(minieditor_parser_tests)

# add_test(
#     NAME minieditor.parser
#     COMMAND minieditor_parser_tests
# )

# set_tests_properties(minieditor.parser
#     PROPERTIES
#         LABELS "unit;parser"
# )
