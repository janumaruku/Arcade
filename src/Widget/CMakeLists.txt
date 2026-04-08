add_library(widget STATIC Units.cpp
        Widget.cpp)

target_include_directories(widget PUBLIC include)

target_link_libraries(widget warning_options)

set_target_properties(widget PROPERTIES POSITION_INDEPENDENT_CODE ON)
