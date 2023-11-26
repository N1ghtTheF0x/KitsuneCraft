cmake_minimum_required(VERSION 3.22)

project(KitsuneCraft)

set(BUILD_SHARED_LIBS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# set output directories for all builds (Debug, Release, etc.)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/lib )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/lib )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/bin )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

add_subdirectory(glad)
add_subdirectory(glm)
set(SDL_TEST OFF)
add_subdirectory(SDL)
set(SDL2IMAGE_SAMPLES OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

set(SOURCE_FILES
    source/app.cpp
    source/context.cpp
    source/texture.cpp
    
    source/utils/sdl.cpp
    source/shaders/fragment.hpp
    source/shaders/vertex.hpp
)

file(GLOB_RECURSE INCLUDE_HEADERS include/*.hpp)
set(LIB_NAME lib${PROJECT_NAME_LOWER})

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${INCLUDE_HEADERS})

target_link_libraries(${LIB_NAME} PRIVATE glad SDL2 SDL2main)
target_include_directories(${LIB_NAME} PUBLIC SDL/include glm include glad/include stb)

add_executable(${PROJECT_NAME} main.cpp)

add_dependencies(${PROJECT_NAME} ${LIB_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC include)