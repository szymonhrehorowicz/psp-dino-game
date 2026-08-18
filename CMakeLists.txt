cmake_minimum_required(VERSION 3.11)

project(hello)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(${PROJECT_NAME} ./src/main.c)

target_sources(${PROJECT_NAME} PRIVATE
    ./src/exit.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ./incl
)

target_link_libraries(${PROJECT_NAME} PRIVATE
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