cmake_minimum_required(VERSION 3.11)

project(hello)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CXX_STANDARD 17 REQUIRED)

add_subdirectory(system)

add_executable(${PROJECT_NAME} ./src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ./incl
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    system
    pspdebug
    pspdisplay
    pspge
)

create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH NULL
    BACKGROUND_PATH NULL
    PREVIEW_PATH NULL
    TITLE ${PROJECT_NAME}
    VERSION 01.00
)