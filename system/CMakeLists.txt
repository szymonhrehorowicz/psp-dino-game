add_library(system STATIC
    src/exit.cpp
    src/controller.cpp
    src/graphics/sprite.cpp
)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

target_include_directories(system
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/incl
)

# Keep the PSP system libraries available to this library as well.
target_link_libraries(system
    PUBLIC
        pspdebug
        pspdisplay
        pspge
        pspctrl

        SDL3::SDL3
)