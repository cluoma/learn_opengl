cmake_minimum_required(VERSION 3.26)
project(learnOGL)

set(CMAKE_CXX_STANDARD 23)

include_directories(include .)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

########################################
## 1.Getting Started
########################################
# Hello Triangle
add_executable(helloTriangle src/1GettingStarted/helloTriangle.cpp src/glad.c)
target_link_libraries(helloTriangle ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Hello Triangle Exercise
add_executable(helloTriangleExercise src/1GettingStarted/helloTriangleExercise.cpp src/glad.c)
target_link_libraries(helloTriangleExercise ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Shaders
add_executable(shaders src/1GettingStarted/shaders.cpp src/glad.c)
target_link_libraries(shaders ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Shaders Exercise
add_executable(shadersExercise src/1GettingStarted/shadersExercise.cpp src/glad.c
        src/shader.h)
target_link_libraries(shadersExercise ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Textures
add_executable(textures src/1GettingStarted/Textures/textures.cpp  src/glad.c
        src/shader.h src/stb_image.cpp)
target_link_libraries(textures ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Transformations
add_executable(transformations src/1GettingStarted/Transformations/transformations.cpp src/glad.c
        src/shader.h src/stb_image.cpp)
target_link_libraries(transformations ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Coord Systems
add_executable(coord_systems src/1GettingStarted/CoordSystems/coordSystems.cpp src/glad.c
        src/shader.h src/stb_image.cpp)
target_link_libraries(coord_systems ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Camera
add_executable(camera src/1GettingStarted/Camera/camera.cpp src/glad.c
        src/shader.h src/stb_image.cpp)
target_link_libraries(camera ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})

########################################
## 2. Lighting
########################################
# Colors
add_executable(colors src/2Lighting/Colors/colors.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(colors ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Basic Lighting
add_executable(basic_lighting src/2Lighting/BasicLighting/basicLighting.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(basic_lighting ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Materials
add_executable(materials src/2Lighting/Materials/materials.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(materials ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Sphere Experiment
add_executable(sphere_experiment src/2Lighting/SphereExperiment/sphereExperiemt.cpp
        src/2Lighting/SphereExperiment/sphere.cpp
        src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(sphere_experiment ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Lighting Maps
add_executable(lighting_maps src/2Lighting/LightingMaps/lightingMaps.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(lighting_maps ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Light Casters
add_executable(light_casters src/2Lighting/LightCasters/lightCasters.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(light_casters ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
