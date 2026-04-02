add_library(arcade_ncurses SHARED NcursesDisplay.cpp
        UnitView.cpp)

target_include_directories(arcade_ncurses PUBLIC include)

target_link_libraries(arcade_ncurses display_interface ncursesw warning_options)

set_target_properties(arcade_ncurses PROPERTIES POSITION_INDEPENDENT_CODE ON)

set_target_properties(arcade_ncurses PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
