add_library(arcade_pacman SHARED PacmanGame.cpp)

target_include_directories(arcade_pacman PUBLIC include)

target_link_libraries(arcade_pacman widget game_interface  )

set_target_properties(arcade_pacman PROPERTIES POSITION_INDEPENDENT_CODE ON)

set_target_properties(arcade_pacman PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)