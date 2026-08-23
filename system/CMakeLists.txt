add_library(system STATIC
    src/exit.cpp
    src/controller.cpp
    src/graphics/sprite.cpp
)

target_include_directories(system
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/incl
)

target_link_libraries(system PUBLIC library)