qt_add_executable(minieditor_gui
  main.cpp
)

target_link_libraries(minieditor_gui
  PRIVATE
    MiniEditor::UI
)

target_compile_features(minieditor_gui
  PRIVATE
    cxx_std_20
)

minieditor_enable_warnings(minieditor_gui)
minieditor_enable_sanitizers(minieditor_gui)
