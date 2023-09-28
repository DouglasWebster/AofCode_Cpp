set(path /mnt/DEV/cpp_work/AofCode_Cpp/src/campaigns/2022)
cmake_path(GET path FILENAME this_directory)

if(NOT EXISTS "/mnt/DEV/cpp_work/AofCode_Cpp/src/campaigns/2022/day01/2022_day01.hpp")
    message("Creating standard header file for this days solution.")
    configure_file(
        "/mnt/DEV/cpp_work/AofCode_Cpp/configured_files/day_details.hpp.in" 
        "/mnt/DEV/cpp_work/AofCode_Cpp/src/campaigns/2022/day01/2022_day01.hpp")
endif()

if(NOT EXISTS "/mnt/DEV/cpp_work/AofCode_Cpp/src/campaigns/2022/day01/2022_day01.cpp")
    message("Creating standard code file for this days solution.")
    configure_file(
        "/mnt/DEV/cpp_work/AofCode_Cpp/configured_files/day_details.cpp.in" 
        "/mnt/DEV/cpp_work/AofCode_Cpp/src/campaigns/2022/day01/2022_day01.cpp")
endif()

if(NOT EXISTS "/mnt/DEV/cpp_work/AofCode_Cpp/src/campaigns/2022/day01/main.cpp")
    message("Creating standard main.cpp file for this days solution.")
    configure_file(
        "/mnt/DEV/cpp_work/AofCode_Cpp/configured_files/day_main.cpp.in" 
        "/mnt/DEV/cpp_work/AofCode_Cpp/src/campaigns/2022/day01/main.cpp")
endif()


add_executable(2022-day01 main.cpp)
