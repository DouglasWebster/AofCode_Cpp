add_executable(tests_2022 tests.cpp)

target_link_libraries(
  tests_2022
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

catch_discover_tests(
    tests_2022
  TEST_PREFIX
  "Year 2022: "
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "Year 2022: "
  OUTPUT_SUFFIX
  .xml)