cmake_minimum_required(VERSION 3.11)

project(DinoGame)

option(PSP_DEBUG_PRX "Build a PRX for PSPLink debugging" OFF)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
set(CMAKE_C_FLAGS_DEBUG "-g3 -Og -fno-omit-frame-pointer -fno-inline -fno-optimize-sibling-calls"
    CACHE STRING "C Debug compiler flags" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Og -fno-omit-frame-pointer -fno-inline -fno-optimize-sibling-calls"
    CACHE STRING "C++ Debug compiler flags" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(library)
add_subdirectory(system)

add_executable(${PROJECT_NAME} 
    ./game/src/main.cpp
    ./game/src/actions/jump.cpp
    ./game/src/actions/move_left.cpp
    ./game/src/actions/collision.cpp
)

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

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/dead.png
    ${CMAKE_CURRENT_BINARY_DIR}/dead.png
    COPYONLY
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ./game/incl
)

if(PSP_DEBUG_PRX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PSP_DEBUG_PRX)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    system
    library
    pspgu
    pspge
    pspdisplay
    pspctrl
    pspdebug
)

if(PSP_DEBUG_PRX)
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        BUILD_PRX
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
        VERSION 01.00
    )
else()
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
        VERSION 01.00
    )
endif()

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/psp/${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/EBOOT.PBP
        ${CMAKE_BINARY_DIR}/psp/${PROJECT_NAME}/EBOOT.PBP
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/resources/idle.png
        ${CMAKE_BINARY_DIR}/psp/${PROJECT_NAME}/idle.png
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/resources/dead.png
        ${CMAKE_BINARY_DIR}/psp/${PROJECT_NAME}/dead.png
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/resources/grass.png
        ${CMAKE_BINARY_DIR}/psp/${PROJECT_NAME}/grass.png
)