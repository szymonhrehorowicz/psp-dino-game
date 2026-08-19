add_library(library STATIC
    src/dummy.cpp
)

target_include_directories(library
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/incl
)

# Keep the PSP system libraries available to this library as well.
target_link_libraries(library
    PUBLIC
)