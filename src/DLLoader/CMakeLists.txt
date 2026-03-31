add_library(dl_loader STATIC DlLoader.cpp)

target_include_directories(dl_loader PUBLIC include)

target_link_libraries(dl_loader warning_options)
