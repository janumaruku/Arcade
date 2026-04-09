add_executable(arcade main.cpp
        Core.cpp
        AScene.cpp
        GameListScene.cpp
        DisplayListScene.cpp)

target_include_directories(arcade PUBLIC include)

target_link_libraries(arcade dl_loader
        display_interface
        warning_options)

set_target_properties(arcade PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
