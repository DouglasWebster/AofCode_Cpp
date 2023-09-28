add_executable(2022_day01_test day01_test.cpp ${CMAKE_SOURCE_DIR}/src/campaigns/2022/day01/2022_day01.cpp)
target_link_libraries(
  2022_day01_test
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

target_include_directories(2022_day01_test PRIVATE ${CMAKE_SOURCE_DIR}/src/campaigns/2022/day01)

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(
    2022_day01_test
  TEST_PREFIX
  "campaign 2022 day 01 tests: "
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "campaign 2022 day 01 tests: "
  OUTPUT_SUFFIX
  .xml)
