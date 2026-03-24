add_library(widget STATIC Units.cpp
        Widget.cpp)

target_include_directories(widget PUBLIC include)

target_link_libraries(widget warning_options)
