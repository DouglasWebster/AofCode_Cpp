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

add_subdirectory(day01)