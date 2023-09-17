include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(AofCode_Cpp_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(AofCode_Cpp_setup_options)
  option(AofCode_Cpp_ENABLE_HARDENING "Enable hardening" OFF)
  option(AofCode_Cpp_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    AofCode_Cpp_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    AofCode_Cpp_ENABLE_HARDENING
    OFF)

  AofCode_Cpp_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR AofCode_Cpp_PACKAGING_MAINTAINER_MODE)
    option(AofCode_Cpp_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(AofCode_Cpp_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(AofCode_Cpp_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(AofCode_Cpp_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(AofCode_Cpp_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(AofCode_Cpp_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(AofCode_Cpp_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(AofCode_Cpp_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(AofCode_Cpp_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(AofCode_Cpp_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(AofCode_Cpp_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(AofCode_Cpp_ENABLE_PCH "Enable precompiled headers" OFF)
    option(AofCode_Cpp_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(AofCode_Cpp_ENABLE_IPO "Enable IPO/LTO" ON)
    option(AofCode_Cpp_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(AofCode_Cpp_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(AofCode_Cpp_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(AofCode_Cpp_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(AofCode_Cpp_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(AofCode_Cpp_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(AofCode_Cpp_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(AofCode_Cpp_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(AofCode_Cpp_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(AofCode_Cpp_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(AofCode_Cpp_ENABLE_PCH "Enable precompiled headers" OFF)
    option(AofCode_Cpp_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      AofCode_Cpp_ENABLE_IPO
      AofCode_Cpp_WARNINGS_AS_ERRORS
      AofCode_Cpp_ENABLE_USER_LINKER
      AofCode_Cpp_ENABLE_SANITIZER_ADDRESS
      AofCode_Cpp_ENABLE_SANITIZER_LEAK
      AofCode_Cpp_ENABLE_SANITIZER_UNDEFINED
      AofCode_Cpp_ENABLE_SANITIZER_THREAD
      AofCode_Cpp_ENABLE_SANITIZER_MEMORY
      AofCode_Cpp_ENABLE_UNITY_BUILD
      AofCode_Cpp_ENABLE_CLANG_TIDY
      AofCode_Cpp_ENABLE_CPPCHECK
      AofCode_Cpp_ENABLE_COVERAGE
      AofCode_Cpp_ENABLE_PCH
      AofCode_Cpp_ENABLE_CACHE)
  endif()

  AofCode_Cpp_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (AofCode_Cpp_ENABLE_SANITIZER_ADDRESS OR AofCode_Cpp_ENABLE_SANITIZER_THREAD OR AofCode_Cpp_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(AofCode_Cpp_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(AofCode_Cpp_global_options)
  if(AofCode_Cpp_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    AofCode_Cpp_enable_ipo()
  endif()

  AofCode_Cpp_supports_sanitizers()

  if(AofCode_Cpp_ENABLE_HARDENING AND AofCode_Cpp_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR AofCode_Cpp_ENABLE_SANITIZER_UNDEFINED
       OR AofCode_Cpp_ENABLE_SANITIZER_ADDRESS
       OR AofCode_Cpp_ENABLE_SANITIZER_THREAD
       OR AofCode_Cpp_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${AofCode_Cpp_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${AofCode_Cpp_ENABLE_SANITIZER_UNDEFINED}")
    AofCode_Cpp_enable_hardening(AofCode_Cpp_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(AofCode_Cpp_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(AofCode_Cpp_warnings INTERFACE)
  add_library(AofCode_Cpp_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  AofCode_Cpp_set_project_warnings(
    AofCode_Cpp_warnings
    ${AofCode_Cpp_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(AofCode_Cpp_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(AofCode_Cpp_options)
  endif()

  include(cmake/Sanitizers.cmake)
  AofCode_Cpp_enable_sanitizers(
    AofCode_Cpp_options
    ${AofCode_Cpp_ENABLE_SANITIZER_ADDRESS}
    ${AofCode_Cpp_ENABLE_SANITIZER_LEAK}
    ${AofCode_Cpp_ENABLE_SANITIZER_UNDEFINED}
    ${AofCode_Cpp_ENABLE_SANITIZER_THREAD}
    ${AofCode_Cpp_ENABLE_SANITIZER_MEMORY})

  set_target_properties(AofCode_Cpp_options PROPERTIES UNITY_BUILD ${AofCode_Cpp_ENABLE_UNITY_BUILD})

  if(AofCode_Cpp_ENABLE_PCH)
    target_precompile_headers(
      AofCode_Cpp_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(AofCode_Cpp_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    AofCode_Cpp_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(AofCode_Cpp_ENABLE_CLANG_TIDY)
    AofCode_Cpp_enable_clang_tidy(AofCode_Cpp_options ${AofCode_Cpp_WARNINGS_AS_ERRORS})
  endif()

  if(AofCode_Cpp_ENABLE_CPPCHECK)
    AofCode_Cpp_enable_cppcheck(${AofCode_Cpp_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(AofCode_Cpp_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    AofCode_Cpp_enable_coverage(AofCode_Cpp_options)
  endif()

  if(AofCode_Cpp_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(AofCode_Cpp_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(AofCode_Cpp_ENABLE_HARDENING AND NOT AofCode_Cpp_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR AofCode_Cpp_ENABLE_SANITIZER_UNDEFINED
       OR AofCode_Cpp_ENABLE_SANITIZER_ADDRESS
       OR AofCode_Cpp_ENABLE_SANITIZER_THREAD
       OR AofCode_Cpp_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    AofCode_Cpp_enable_hardening(AofCode_Cpp_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
