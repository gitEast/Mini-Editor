add_executable(minieditor_cli 
  main.cpp
)

target_link_libraries(minieditor_cli
  PRIVATE
    MiniEditor::Core
)
target_compile_features(minieditor_cli
  PRIVATE
    cxx_std_20
)

minieditor_enable_warnings(minieditor_cli)
minieditor_enable_sanitizers(minieditor_cli)
