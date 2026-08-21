cmake_minimum_required(VERSION 3.11)

project(hello)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(library)
add_subdirectory(system)

add_executable(${PROJECT_NAME} 
    ./game/src/main.cpp
    ./game/src/actions/jump.cpp
    ./game/src/actions/move_left.cpp
)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/grass.png
    ${CMAKE_CURRENT_BINARY_DIR}/grass.png
    COPYONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/idle.png
    ${CMAKE_CURRENT_BINARY_DIR}/idle.png
    COPYONLY
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ./game/incl
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    system
    library
    pspdebug
    pspdisplay
    pspge
    pspctrl

    SDL3::SDL3
)

create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH NULL
    BACKGROUND_PATH NULL
    PREVIEW_PATH NULL
    TITLE ${PROJECT_NAME}
    VERSION 01.00
)