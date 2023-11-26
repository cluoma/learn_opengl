#include <stdint.h>
#include <iostream>
#include "glad/glad.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/gl.h>

#include <stb/stb_image.h>
#include "src/shader.h"
#include "src/camera.h"
#include "src/2Lighting/SphereExperiment/sphere.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

//Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main() {

    Sphere mysphere(500, 500);


    // code without checking for errors
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // flags
    int32_t WindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

    // init SDL window
    SDL_Window *Window = SDL_CreateWindow(
            "LearnOpenGL",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            WindowFlags
    );
    // SDL_SetWindowMouseGrab(Window, SDL_TRUE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // init GL context
    SDL_GLContext Context = SDL_GL_CreateContext(Window);
    SDL_GL_MakeCurrent(Window, Context);

    // load GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // set viewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    // enable z-buffer
    glEnable(GL_DEPTH_TEST);

    // compile shaders
    Shader lightingShader("src/2Lighting/SphereExperiment/colors.vert", "src/2Lighting/SphereExperiment/colors.frag");
    Shader lightCubeShader("src/2Lighting/SphereExperiment/light_cube.vert", "src/2Lighting/SphereExperiment/light_cube.frag");

    // build vertex objects for cubes
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ---------------------------
    // try to add the sphere
    // unsigned int sphereVAO, sphereVBO, sphereEBO;
    // glGenVertexArrays(1, &sphereVAO);
    // glGenBuffers(1, &sphereVBO);
    // glGenBuffers(1, &sphereEBO);
    // // bind VAO
    // glBindVertexArray(sphereVAO);
    // // create vertex buffer object from 'vertices[]' and 'indices[]'
    // std::vector<float> sphereVertices = mysphere.get_vertices();
    // std::vector<unsigned int> sphereIndices = mysphere.get_indices();
    // // std::cout << sphereIndices.at(0) << ", " << sphereIndices.at(1) << ", " << sphereIndices.at(2) << ", " << std::endl;
    // for (int i = 0; i < sphereVertices.size()-3; i+=3)
    // {
    //     std::cout << "(" << sphereVertices.at(i) << ", " << sphereVertices.at(i+1) << ", " << sphereVertices.at(i+2) << ")" << std::endl;
    // }
    // glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    // glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), sphereVertices.data(), GL_STATIC_DRAW);
    // // glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSphere), verticesSphere, GL_STATIC_DRAW);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(unsigned int), sphereIndices.data(), GL_STATIC_DRAW);
    // // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesSphere), indicesSphere, GL_STATIC_DRAW);
    // // set the vertex attribute pointers
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // -------------------------------
    unsigned int sphereVAO, sphereVBO, sphereEBO;
    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    // bind VAO
    glBindVertexArray(sphereVAO);
    // create vertex buffer object from 'vertices[]' and 'indices[]'
    std::vector<float> sphereVertices = mysphere.get_vertex_attribs();
    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), sphereVertices.data(), GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSphere), verticesSphere, GL_STATIC_DRAW);
    // set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // don't forget to use the corresponding shader program first (to set the uniform)
    lightingShader.use();
    lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
    lightingShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

    // render loop
    int32_t Running = 1;
    int32_t FullScreen = 0;

    float deltaTime = 0.0f;
    float lastFrame = (float)SDL_GetTicks()/1000.0f;

    while (Running)
    {
        // update frame delta
        float currentFrame = (float)SDL_GetTicks()/1000.0f;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // continuous key state
        const Uint8 * keystate = SDL_GetKeyboardState(nullptr);
        const float cameraSpeed = 5.0f * deltaTime;
        SDL_PumpEvents();
        if (keystate[SDL_SCANCODE_W])
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (keystate[SDL_SCANCODE_S])
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (keystate[SDL_SCANCODE_A])
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (keystate[SDL_SCANCODE_D])
            camera.ProcessKeyboard(RIGHT, deltaTime);

        // SDL single events
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_KEYDOWN)
            {
                switch (Event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        Running = 0;
                        break;
                    case 'f':
                        FullScreen = !FullScreen;
                        if (FullScreen)
                        {
                            SDL_SetWindowFullscreen(Window, WindowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                        }
                        else
                        {
                            SDL_SetWindowFullscreen(Window, WindowFlags);
                        }
                        break;
                    default:
                        break;
                }
            }
            else if (Event.type == SDL_MOUSEBUTTONDOWN)
            {
                switch (Event.button.button)
                {
                    case SDL_BUTTON_RIGHT:
                        if (SDL_GetRelativeMouseMode() == SDL_TRUE)
                            SDL_SetRelativeMouseMode(SDL_FALSE);
                        else
                            SDL_SetRelativeMouseMode(SDL_TRUE);
                        break;
                    default:
                        break;
                }
            }
            else if (Event.type == SDL_MOUSEMOTION && SDL_GetRelativeMouseMode() == SDL_TRUE)
            {
                camera.ProcessMouseMovement(static_cast<float>(Event.motion.xrel), static_cast<float>(Event.motion.yrel) * (-1));
            }
            else if (Event.type == SDL_MOUSEWHEEL && SDL_GetRelativeMouseMode() == SDL_TRUE)
            {
                camera.ProcessMouseScroll(static_cast<float>(Event.wheel.y) * 5);
            }
            else if (Event.type == SDL_WINDOWEVENT)
            {
                if(Event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    std::cout << "window resized: [" << Event.window.data1 << ", " << Event.window.data2 << "]" << std::endl;
                    SCREEN_WIDTH = Event.window.data1;
                    SCREEN_HEIGHT = Event.window.data2;
                    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
            }
            else if (Event.type == SDL_QUIT)
            {
                Running = 0;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);
        // material properties
        // orange cube
        // lightingShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        // lightingShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        // lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        // lightingShader.setFloat("material.shininess", 32.0f);
        // green rubber cube
        lightingShader.setVec3("material.ambient", 0.0f, 0.05f, 0.0f);
        lightingShader.setVec3("material.diffuse", 0.4f, 0.5f, 0.4f);
        lightingShader.setVec3("material.specular", 0.04f, 0.7f, 0.04f);
        lightingShader.setFloat("material.shininess", 0.078125f*128.0f);
        // light properties
        lightingShader.setVec3("light.position", lightPos.x, lightPos.y, lightPos.z);
        lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        lightingShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        // change light over time
        // glm::vec3 lightColor;
        // lightColor.x = sin((float)SDL_GetTicks()/1000.0f * 2.0f);
        // lightColor.y = sin((float)SDL_GetTicks()/1000.0f * 0.7f);
        // lightColor.z = sin((float)SDL_GetTicks()/1000.0f * 1.3f);
        // glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
        // glm::vec3 ambientColor = lightColor * glm::vec3(0.2f);
        // lightingShader.setVec3("light.ambient", ambientColor.x, ambientColor.y, ambientColor.z);
        // lightingShader.setVec3("light.diffuse", diffuseColor.x, diffuseColor.y, diffuseColor.z);
        // lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // update position of light
        // glm::vec3 nlightPos = lightPos;
        // nlightPos.x = cos((1.0f/360.0f)*2.0f*3.1415962f)*lightPos.x + sin((1.0f/360.0f)*2.0f*3.1415962f)*lightPos.z;
        // nlightPos.z = (-1.0f)*sin((1.0f/360.0f)*2*3.1415962f)*lightPos.x + cos((1.0f/360.0f)*2.0f*3.1415962f)*lightPos.z;
        // lightPos = nlightPos;
        // lightingShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", glm::value_ptr(projection));
        lightingShader.setMat4("view", glm::value_ptr(view));

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", glm::value_ptr(model));

        // render the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // also draw the lamp object
        lightCubeShader.use();
        lightCubeShader.setVec3("lightColor",  1.0f, 1.0f, 0.5f);
        // lightCubeShader.setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);
        lightCubeShader.setMat4("projection", glm::value_ptr(projection));
        lightCubeShader.setMat4("view", glm::value_ptr(view));
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        // make the cube always face the 0, 0, 0
        float lightAngle = acos(glm::dot(glm::normalize(glm::vec3(lightPos.x, 0.0f, lightPos.z)), glm::vec3(0.0f, 0.0f, 1.0f)));
        if (lightPos.x < 0)
            lightAngle = 2.0f * 3.1415962f - lightAngle;
        model = glm::rotate(model, lightAngle, glm::vec3(0, 1, 0));
        lightCubeShader.setMat4("model", glm::value_ptr(model));

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //lightCubeShader.use();
        lightingShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::translate(model, glm::vec3(2.0f, -2.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f));
        // lightCubeShader.setMat4("model", glm::value_ptr(model));
        lightingShader.setMat4("model", glm::value_ptr(model));
        // green rubber cube
        lightingShader.setVec3("material.ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("material.diffuse", 0.8f, 0.2f, 0.2f);
        lightingShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("material.shininess", 24);
        // light properties
        lightingShader.setVec3("light.position", lightPos.x, lightPos.y, lightPos.z);
        lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        lightingShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        glBindVertexArray(sphereVAO);
        glDrawArrays(GL_TRIANGLES, 0, sphereVertices.size()/2);
        //glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(Window);
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    SDL_GL_DeleteContext(Context);
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}
