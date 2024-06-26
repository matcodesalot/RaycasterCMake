﻿cmake_minimum_required(VERSION 3.16)
project(RaycasterCMake LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

# Fetch and include SFML
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Fetch and include ImGui
FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.9)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(ImGui-SFML)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Copy resources directory to the build directory
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(RaycasterCMake ${SOURCES} ${HEADERS})
target_link_libraries(RaycasterCMake PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML)
target_compile_features(RaycasterCMake PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET RaycasterCMake
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:RaycasterCMake>
        VERBATIM)
endif()

install(TARGETS RaycasterCMake)
