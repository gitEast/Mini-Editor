include_guard(GLOBAL)

function(minieditor_enable_sanitizers target_name)
  if(NOT MINIEDITOR_ENABLE_SANITIZERS)
    return()
  endif()

  if(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang|Clang|GNU")
    target_compile_options(${target_name}
      PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
    target_link_options(${target_name}
      PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
    return()
  endif()

  message(WARNING "Sanitizers are not configured for ${CMAKE_CXX_COMPILE_ID}")
endfunction()

