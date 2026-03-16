add_executable(arcade main.cpp)

target_include_directories(arcade PUBLIC .)

target_link_libraries(arcade test_lib warning_options)

set_target_properties(arcade PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
