set(path ${CMAKE_CURRENT_LIST_DIR})
cmake_path(GET path FILENAME this_directory)

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/${parent_directory}_${this_directory}.hpp")
    message("Creating standard header file for this days solution.")
    configure_file(
        "${CMAKE_SOURCE_DIR}/configured_files/day_details.hpp.in" 
        "${CMAKE_CURRENT_LIST_DIR}/${parent_directory}_${this_directory}.hpp")
endif()

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
    message("Creating standard main.cpp file for this days solution.")
    configure_file(
        "${CMAKE_SOURCE_DIR}/configured_files/day_main.cpp.in" 
        "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
endif()

add_executable("${parent_directory}-${this_directory}" main.cpp)