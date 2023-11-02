set(path ${CMAKE_CURRENT_LIST_DIR})
cmake_path(GET path FILENAME this_directory)

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/day21_test.cpp")
    message("Creating standard test file for this days solution.")
    configure_file(
        "${CMAKE_SOURCE_DIR}/configured_files/day_test.cpp.in" 
        "${CMAKE_CURRENT_LIST_DIR}/day21_test.cpp"
        @ONLY)
endif()

add_executable(2022_day21_test day21_test.cpp
    ${CMAKE_SOURCE_DIR}/src/campaigns/2022/day21/2022_day21.cpp)

target_link_libraries(
  2022_day21_test
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

target_include_directories(
    2022_day21_test 
    PRIVATE ${CMAKE_SOURCE_DIR}/src/campaigns/2022/day21)

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(
  2022_day21_test 
  TEST_PREFIX
  "campaign 2022 day21 tests: "
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "campaign 2022 day21 tests: "
  OUTPUT_SUFFIX
  .xml)
