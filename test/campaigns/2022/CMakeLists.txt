cmake_minimum_required(VERSION 3.15...3.23)

project(campaing_test LANGUAGES CXX)

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

# --- Find all the current test days ---

set(campaign_year ${CMAKE_CURRENT_LIST_DIR})
cmake_path(GET campaign_year FILENAME parent_directory)

message("")
message("Scanning directory ${parent_directory} for active test days}")

foreach(day_no RANGE 1 25)
    if(${day_no} LESS 10)
        set(dir_name day0${day_no})
    else()
        set(dir_name day${day_no})
    endif()

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${dir_name}/")
        message("   Found ${dir_name}")
        if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${dir_name}/CMakeLists.txt")
            message("Creating CMakeLists.txt file for this days solution.")
            configure_file(
                "${CMAKE_SOURCE_DIR}/configured_files/CMakeLists.txt.test.in" 
                "${CMAKE_CURRENT_SOURCE_DIR}/${dir_name}/CMakeLists.txt"
                @ONLY)
        endif()
        add_subdirectory(${dir_name})
    endif()
    
endforeach()
message("")