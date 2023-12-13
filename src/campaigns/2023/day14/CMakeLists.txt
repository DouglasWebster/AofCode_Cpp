set(path ${CMAKE_CURRENT_LIST_DIR})
cmake_path(GET path FILENAME this_directory)

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/2023_day14.hpp")
    message("Creating standard header file for this days solution.")
    configure_file(
        "${CMAKE_SOURCE_DIR}/configured_files/day_details.hpp.in" 
        "${CMAKE_CURRENT_LIST_DIR}/2023_day14.hpp"
        @ONLY)
endif()

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/2023_day14.cpp")
    message("Creating standard code file for this days solution.")
    configure_file(
        "${CMAKE_SOURCE_DIR}/configured_files/day_details.cpp.in" 
        "${CMAKE_CURRENT_LIST_DIR}/2023_day14.cpp"
        @ONLY)
endif()

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
    message("Creating standard main.cpp file for this days solution.")
    configure_file(
        "${CMAKE_SOURCE_DIR}/configured_files/day_main.cpp.in" 
        "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
        @ONLY)
endif()


add_executable(2023-day14 main.cpp 2023_day14.cpp)

target_link_libraries(
  2023-day14
  PRIVATE AofCode_Cpp::AofCode_Cpp_warnings
          AofCode_Cpp::AofCode_Cpp_options
          AofCode_Cpp::aoc_library
)

target_compile_definitions(2023-day14 PRIVATE CURRENT_LIST_DIR="${CMAKE_CURRENT_LIST_DIR}")

