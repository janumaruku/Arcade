add_library(arcade_sdl SHARED SdlDisplay.cpp
        include/SdlDisplay.hpp)

target_include_directories(arcade_sdl PUBLIC include)

target_link_libraries(arcade_sdl
        display_interface
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer
        warning_options
)

set_target_properties(arcade_sdl PROPERTIES POSITION_INDEPENDENT_CODE ON)

set_target_properties(arcade_sdl PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
