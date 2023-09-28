set(path ${CMAKE_CURRENT_LIST_DIR})
cmake_path(GET path FILENAME this_directory)

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/2022_day01.hpp")
    message("Creating standard header file for this days solution.")
    configure_file(
        "${CMAKE_SOURCE_DIR}/configured_files/day_details.hpp.in" 
        "${CMAKE_CURRENT_LIST_DIR}/2022_day01.hpp"
        @ONLY)
endif()

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/2022_day01.cpp")
    message("Creating standard code file for this days solution.")
    configure_file(
        "${CMAKE_SOURCE_DIR}/configured_files/day_details.cpp.in" 
        "${CMAKE_CURRENT_LIST_DIR}/2022_day01.cpp"
        @ONLY)
endif()

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
    message("Creating standard main.cpp file for this days solution.")
    configure_file(
        "${CMAKE_SOURCE_DIR}/configured_files/day_main.cpp.in" 
        "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
        @ONLY)
endif()


add_executable(2022-day01 main.cpp)
