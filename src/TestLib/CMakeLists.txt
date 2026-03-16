add_library(test_lib SHARED test_lib.cpp)

target_include_directories(test_lib PUBLIC .)

set_target_properties(test_lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

set_target_properties(test_lib PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
