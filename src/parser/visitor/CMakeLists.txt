add_library(minieditor_html_renderer STATIC HtmlRenderVisitor.cpp)
add_library(MiniEditor::HtmlRenderer ALIAS minieditor_html_renderer)

target_sources(minieditor_html_renderer
  PRIVATE
    Visitor.h
    HtmlRenderVisitor.h
)

target_include_directories(minieditor_html_renderer
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)
target_compile_features(minieditor_html_renderer
  PUBLIC
    cxx_std_20
)
target_link_libraries(minieditor_html_renderer
  PUBLIC
    MiniEditor::AST
)

minieditor_enable_warnings(minieditor_html_renderer)
minieditor_enable_sanitizers(minieditor_html_renderer)
