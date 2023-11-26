add_library(glad STATIC src/gl.c)

find_package(OpenGL REQUIRED)

target_include_directories(glad PUBLIC include ${OPENGL_INCLUDE_DIR})
target_link_libraries(glad PRIVATE ${OPENGL_LIBRARIES})