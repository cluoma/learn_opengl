cmake_minimum_required(VERSION 3.26)
project(learnOGL)

set(CMAKE_CXX_STANDARD 23)

include_directories(include . ./src/imgui ./src/imgui/backends ./src/imgui/misc/cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(IMGUI_SOURCES
        src/imgui/imconfig.h
        src/imgui/imgui.cpp
        src/imgui/imgui.h
        src/imgui/imgui_demo.cpp
        src/imgui/imgui_draw.cpp
        src/imgui/imgui_internal.h
        src/imgui/imgui_tables.cpp
        src/imgui/imgui_widgets.cpp
        src/imgui/imstb_rectpack.h
        src/imgui/imstb_textedit.h
        src/imgui/imstb_truetype.h
        src/imgui/backends/imgui_impl_opengl3.cpp
        src/imgui/backends/imgui_impl_opengl3.h
        src/imgui/backends/imgui_impl_sdl2.cpp
        src/imgui/backends/imgui_impl_sdl2.h
        src/imgui/misc/cpp/imgui_stdlib.cpp
        src/imgui/misc/cpp/imgui_stdlib.h
)

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
# Spotlight
add_executable(spotlight src/2Lighting/Spolight/spotlight.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(spotlight ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Multiple Light Sources
add_executable(multiple_light_sources src/2Lighting/MultipleLightSources/multipleLightSources.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(multiple_light_sources ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Multiple Light Sources ImGUI
add_executable(multiple_light_sources_imgui src/2Lighting/MultipleLightSourcesImgui/multipleLightSourcesImgui.cpp
        src/glad.c src/shader.h src/camera.h src/stb_image.cpp
        ${IMGUI_SOURCES}
        src/Mesh.cpp src/Mesh.h src/Model.cpp src/Model.h)
target_link_libraries(multiple_light_sources_imgui ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} assimp)


########################################
## 3. Models
########################################
# Models
add_executable(models src/3Models/Models/models.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp
        src/Mesh.cpp src/Mesh.h src/Model.h src/Model.cpp)
target_link_libraries(models ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} assimp)
# Desk Models
add_executable(desk_model src/3Models/DeskModel/models.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp
        src/Mesh.cpp src/Mesh.h src/Model.h src/Model.cpp
        src/3Models/DeskModel/LightCube.cpp src/3Models/DeskModel/LightCube.h)
target_link_libraries(desk_model ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} assimp)


########################################
## 4. Advanced OpenGL
########################################
# Depth Testing
add_executable(depth_testing src/4AdvancedOpenGL/DepthTesting/depthTesting.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(depth_testing ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Stencile Testing
add_executable(stencil_testing src/4AdvancedOpenGL/StencilTesting/stencilTesting.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(stencil_testing ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Blending Alpha Discard
add_executable(blending_alpha_discard src/4AdvancedOpenGL/Blending/blendingAlphaDiscard.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(blending_alpha_discard ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Blending Alpha
add_executable(blending_alpha src/4AdvancedOpenGL/Blending/blendingAlpha.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(blending_alpha ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Face Culling
add_executable(face_culling src/4AdvancedOpenGL/FaceCulling/faceCulling.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(face_culling ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Framebuffers
add_executable(framebuffers src/4AdvancedOpenGL/Framebuffers/framebuffers.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(framebuffers ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
# Cube Maps
add_executable(cube_maps src/4AdvancedOpenGL/CubeMaps/cubeMaps.cpp src/glad.c
        src/shader.h src/camera.h src/stb_image.cpp)
target_link_libraries(cube_maps ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})

