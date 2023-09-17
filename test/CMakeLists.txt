cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(AofCode_Cpp CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET AofCode_Cpp_options)
    message(FATAL_ERROR "Requiered config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

# Provide a simple smoke test to make sure that the CLI works and can display a --help message
add_test(NAME cli.has_help COMMAND cli_test --help)

# Provide a test to verify that the version being reported from the application
# matches the version given to CMake. This will be important once you package
# your program. Real world shows that this is the kind of simple mistake that is easy
# to make, but also easy to test for.
add_test(NAME cli.version_matches COMMAND cli_test --version)
set_tests_properties(cli.version_matches PROPERTIES PASS_REGULAR_EXPRESSION "${PROJECT_VERSION}")

add_executable(AoCLib_test AoCLib_tests.cpp)
target_link_libraries(
  AoCLib_test
  PRIVATE AofCode_Cpp::AofCode_Cpp_warnings
          AofCode_Cpp::AofCode_Cpp_options
          AofCode_Cpp::aoc_library
          Catch2::Catch2WithMain)

if(WIN32 AND BUILD_SHARED_LIBS)
  add_custom_command(
    TARGET tests
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:tests> $<TARGET_FILE_DIR:tests>
    COMMAND_EXPAND_LISTS)
endif()

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(
  AoCLib_test
  TEST_PREFIX
  "AoCLib unit tests: "
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "AoCLib unit tests: "
  OUTPUT_SUFFIX
  .xml)

# Add a file containing a set of constexpr tests
# add_executable(constexpr_tests constexpr_tests.cpp)
# target_link_libraries(
#   constexpr_tests
#   PRIVATE AofCode_Cpp::AofCode_Cpp_warnings
#           AofCode_Cpp::AofCode_Cpp_options
#           AofCode_Cpp::aoc_library
#           Catch2::Catch2WithMain)

# catch_discover_tests(
#   constexpr_tests
#   TEST_PREFIX
#   "constexpr."
#   REPORTER
#   XML
#   OUTPUT_DIR
#   .
#   OUTPUT_PREFIX
#   "constexpr."
#   OUTPUT_SUFFIX
#   .xml)

# Disable the constexpr portion of the test, and build again this allows us to have an executable that we can debug when
# things go wrong with the constexpr testing
# add_executable(relaxed_constexpr_tests constexpr_tests.cpp)
# target_link_libraries(
#   relaxed_constexpr_tests
#   PRIVATE AofCode_Cpp::AofCode_Cpp_warnings
#           AofCode_Cpp::AofCode_Cpp_options
#           AofCode_Cpp::aoc_library
#           Catch2::Catch2WithMain)
# target_compile_definitions(relaxed_constexpr_tests PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

# catch_discover_tests(
#   relaxed_constexpr_tests
#   TEST_PREFIX
#   "relaxed_constexpr."
#   REPORTER
#   XML
#   OUTPUT_DIR
#   .
#   OUTPUT_PREFIX
#   "relaxed_constexpr."
#   OUTPUT_SUFFIX
#   .xml)

add_subdirectory(tests_2022)
