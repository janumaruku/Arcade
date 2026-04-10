add_library(game_interface STATIC GameInterface.hpp)

target_link_libraries(game_interface widget)

target_include_directories(game_interface PUBLIC .)

set_target_properties(game_interface PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(display_interface STATIC DisplayInterface.hpp)

target_link_libraries(display_interface widget)

target_include_directories(display_interface PUBLIC .)

set_target_properties(display_interface PROPERTIES POSITION_INDEPENDENT_CODE ON)
