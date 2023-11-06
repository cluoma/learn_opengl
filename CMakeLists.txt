cmake_minimum_required(VERSION 3.26)
project(learnOGL)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Hello Triangle
add_executable(helloTriangle src/1GettingStarted/helloTriangle.cpp src/glad.c)
target_link_libraries(helloTriangle ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Hello Triangle Exercise
add_executable(helloTriangleExercise src/1GettingStarted/helloTriangleExercise.cpp src/glad.c)
target_link_libraries(helloTriangleExercise ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
