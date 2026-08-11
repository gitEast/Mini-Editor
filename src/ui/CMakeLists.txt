add_library(minieditor_ui STATIC
  MainWindow.cpp
)
add_library(MiniEditor::UI ALIAS minieditor_ui)

target_sources(minieditor_ui
  PRIVATE
    MainWindow.h
)

target_include_directories(minieditor_ui
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_compile_features(minieditor_ui
  PUBLIC
    cxx_std_20
)

target_link_libraries(minieditor_ui
  PUBLIC
    MiniEditor::Core
    Qt6::Widgets
)

minieditor_enable_warnings(minieditor_ui)
minieditor_enable_sanitizers(minieditor_ui)