include(GenerateExportHeader)


add_library(aoc_library aoc_library.cpp)



add_library(AofCode_Cpp::aoc_library ALIAS aoc_library)

target_link_libraries(aoc_library PRIVATE AofCode_Cpp_options AofCode_Cpp_warnings)

target_include_directories(aoc_library ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(aoc_library PUBLIC cxx_std_20)

set_target_properties(
  aoc_library
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(aoc_library EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/AofCode_Cpp/aoc_library_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(aoc_library PUBLIC aoc_library_STATIC_DEFINE)
endif()
