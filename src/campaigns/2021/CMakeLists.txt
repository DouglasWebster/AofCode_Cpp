set(campaign_year ${CMAKE_CURRENT_LIST_DIR})
cmake_path(GET campaign_year FILENAME parent_directory)

message("")
message("Scanning directory ${parent_directory} for active days}")

foreach(day_no RANGE 1 25)
    if(${day_no} LESS 10)
        set(dir_name day0${day_no})
    else()
        set(dir_name day${day_no})
    endif()

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${dir_name}/")
        message("   Found ${dir_name}")
        add_subdirectory(${dir_name})
    else()
        message("   Not found ${dir_name}")
    endif()
    
endforeach()
message("")
    