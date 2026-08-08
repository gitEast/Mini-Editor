include_guard(GLOBAL)

function(minieditor_enable_warnings target_name)
  if(MSVC)
    target_compile_options(${target_name} PRIVATE /W4)
    if (MINIEDITOR_WARNINGS_AS_ERRORS)
      target_compile_options(${target_name} PRIVATE /WX)
    endif()
    return()
  endif()

  if(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang|Clang|GNU")
    target_compile_options(${target_name} 
      PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic 
        -Wshadow 
        -Wconversion 
        -Wsign-conversion
    )
    if(MINIEDITOR_WARNINGS_AS_ERRORS)
      target_compile_options(${target_name} 
        PRIVATE 
          -Werror
      )
    endif()
  endif()
endfunction()
