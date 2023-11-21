cmake_minimum_required(VERSION 3.22)

project(KitsuneCraft)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set output directories for all builds (Debug, Release, etc.)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

add_subdirectory(glm)
set(OPTION_BUILD_TOOLS OFF)
set(OPTION_BUILD_EXAMPLES OFF)
add_subdirectory(glbinding)
set(SDL_TEST_LIBRARY OFF)
add_subdirectory(SDL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(TOLOWER ${PROJECT_NAME} LIB_NAME)

add_library(${LIB_NAME} STATIC
    source/app.cpp
    source/app.hpp
    source/sdl.hpp
    source/opengl.cpp
    source/opengl.hpp
    source/shaders/vertex.hpp
    source/shaders/fragment.hpp
)

target_link_libraries(${LIB_NAME} PRIVATE SDL3-shared glbinding glbinding-aux)
target_include_directories(${LIB_NAME} PUBLIC SDL/include glbinding/source/glbinding/include glbinding/source/glbinding-aux/include glm/glm)

add_executable(game main.cpp)
target_link_libraries(game PRIVATE ${LIB_NAME})
target_include_directories(game PUBLIC source)