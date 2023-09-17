add_executable(cli_test cli_test.cpp)

# target_link_libraries(
#     cli_test
#     PRIVATE
#         soko_cpp_tools::soko_cpp_tools_options
#         soko_cpp_tools::soko_cpp_tools_warnings
# )

target_link_system_libraries(
    cli_test
    PRIVATE
        CLI11::CLI11
        fmt::fmt
        spdlog::spdlog
)

target_include_directories(cli_test PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")