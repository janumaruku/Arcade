add_executable(arcade main.cpp)

target_include_directories(arcade PUBLIC .)

target_link_libraries(arcade warning_options)
