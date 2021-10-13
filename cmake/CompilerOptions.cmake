# from: https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md
#

function(set_project_options project_options_target_name)
  option(ENABLE_COVERAGE  "Enable gcov coverage"                      False)
  option(ENABLE_WERROR    "Enable treat compiler warnings as errors"  False)

  set(MSVC_OPTIONS
      /W2           # Baseline reasonable warnings
      /permissive-  # standards conformance mode for MSVC compiler.
      /w14242       # 'identifier': conversion from 'type1' to 'type1', possible loss of data
      /w14254       # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
      /w14263       # 'function': member function does not override any base class virtual member function
      /w14265       # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
      /w14287       # 'operator': unsigned/negative constant mismatch
      /w14296       # 'operator': expression is always 'boolean_value'
      /w14311       # 'variable': pointer truncation from 'type1' to 'type2'
      /w14545       # expression before comma evaluates to a function which is missing an argument list
      /w14546       # function call before comma missing argument list
      /w14547       # 'operator': operator before comma has no effect; expected operator with side-effect
      /w14549       # 'operator': operator before comma has no effect; did you intend 'operator'?
      /w14555       # expression has no effect; expected expression with side- effect
      /w14619       # pragma warning: there is no warning number 'number'
      /w14640       # Enable warning on thread un-safe static member initialization
      /w14826       # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected runtime behavior.
      /w14905       # wide string literal cast to 'LPSTR'
      /w14906       # string literal cast to 'LPWSTR'
      /w14928       # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
      /we4289       # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside the for-loop scope
      )

  set(CLANG_OPTIONS
      -Wall
      -pedantic             # warn if non-standard C++ is used
      -Wcast-align          # warn for potential performance problem casts
      -Wconversion          # warn on type conversions that may lose data
      -Wdouble-promotion    # warn if float is implicit promoted to double
      -Wextra               # reasonable and standard
      -Wformat=2            # warn on security issues around functions that format output (ie printf)
      -Wnon-virtual-dtor    # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
      -Wnull-dereference    # warn if a null dereference is detected
      -Wold-style-cast      # warn for c-style casts
      -Woverloaded-virtual  # warn if you overload (not override) a virtual function
      -Wshadow              # warn the user if a variable declaration shadows one from a parent context
      -Wsign-conversion     # warn on signed-unsigned conversions
      -Wunused              # warn on anything being unused
      )

  set(GCC_OPTIONS
      ${CLANG_OPTIONS}
      -Wduplicated-branches     # warn if if / else branches have duplicated code
      -Wduplicated-cond         # warn if if / else chain has duplicated conditions
      -Wlogical-op              # warn about logical operations being used where bitwise were probably wanted
      -Wmisleading-indentation  # warn if indentation implies blocks where blocks do not exist
      -Wuseless-cast            # warn if you perform a cast to the same type
      )

  if (ENABLE_WERROR)
    set(CLANG_OPTIONS ${CLANG_OPTIONS}  -Werror)
    set(GCC_OPTIONS   ${GCC_OPTIONS}    -Werror)
    set(MSVC_OPTIONS  ${MSVC_OPTIONS}   /WX)
  endif ()

  if (MSVC)
    set(PROJECT_OPTIONS ${MSVC_OPTIONS})
  elseif (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(PROJECT_OPTIONS ${CLANG_OPTIONS})
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PROJECT_OPTIONS ${GCC_OPTIONS})
    target_link_libraries(${project_options_target_name} PRIVATE pthread)
    if (ENABLE_COVERAGE)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage" PARENT_SCOPE) # PARENT_SCOPE required since this is called from a function
      message(STATUS "coverage enabled: ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif ()

  target_compile_options(${project_options_target_name} PRIVATE ${PROJECT_OPTIONS}) # for header-only use INTERFACE

  message(STATUS "Project options: ${PROJECT_OPTIONS}")
  message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
  message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
  message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")

endfunction()
