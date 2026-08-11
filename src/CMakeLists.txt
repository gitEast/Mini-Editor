add_subdirectory(parser)

add_library(minieditor_core INTERFACE)
add_library(MiniEditor::Core ALIAS minieditor_core)

# 聚合生产模块
target_link_libraries(minieditor_core
  INTERFACE
    MiniEditor::AST
    MiniEditor::Lexer
    MiniEditor::Parser
    MiniEditor::HtmlRenderer
)

# Core 不产生库文件
target_compile_features(minieditor_core
  INTERFACE
    cxx_std_20
)

if(MINIEDITOR_BUILD_APP)
  add_subdirectory(app)
endif()
if(MINIEDITOR_BUILD_QT_APP)
  find_package(Qt6 6.2 REQUIRED COMPONENTS Widgets)
  add_subdirectory(ui)
  add_subdirectory(qt_app)
endif()
