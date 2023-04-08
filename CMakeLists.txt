cmake_minimum_required(VERSION 3.21)

project(Chess LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

add_executable(Chess src/main.cpp "src/game.cpp" "src/Pieces/piece.cpp" "src/moves.cpp")
target_link_libraries(Chess PRIVATE sfml-graphics)
target_compile_features(Chess PRIVATE cxx_std_17)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

target_precompile_headers(Chess PRIVATE src/pch.h)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Chess POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Chess> $<TARGET_FILE_DIR:Chess> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Chess)
