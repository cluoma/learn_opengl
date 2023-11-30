#include <stdint.h>
#include <iostream>
#include "glad/glad.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/gl.h>

#include <stb/stb_image.h>
#include "src/shader.h"
#include "src/camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

//Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// function declarations
unsigned int loadTexture(const char * path);

int main() {

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
    Shader lightingShader("src/2Lighting/MultipleLightSources/colors.vert", "src/2Lighting/MultipleLightSources/colors.frag");
    Shader lightCubeShader("src/2Lighting/MultipleLightSources/light_cube.vert", "src/2Lighting/MultipleLightSources/light_cube.frag");


    // ----------------
    // Build vertex objects for cubes
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // ----------------
    // Load Textures
    unsigned int textureContainer = loadTexture("assets/textures/container2.png");
    // the box
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureContainer);
    // the specular map
    unsigned int specularMap = loadTexture("assets/textures/container2_specular.png");
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);


    // ----------------
    // Render Loop
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

        // ----------------
        // Handle Inputs
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


        // ----------------
        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // setup lighting shader
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);
        // material properties
        lightingShader.setInt("material.diffuse", 0);
        lightingShader.setInt("material.specular", 1);
        lightingShader.setFloat("material.shininess", 32);
        // directional light properties
        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light properties
        for (int i = 0; i < 4; i++)
        {
            char uniformName[150];
            sprintf(uniformName, "pointLights[%d].position", i);
            lightingShader.setVec3(uniformName, pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
            sprintf(uniformName, "pointLights[%d].ambient", i);
            lightingShader.setVec3(uniformName, 0.2f, 0.2f, 0.2f);
            sprintf(uniformName, "pointLights[%d].diffuse", i);
            lightingShader.setVec3(uniformName, 0.8f, 0.8f, 0.8f);
            sprintf(uniformName, "pointLights[%d].specular", i);
            lightingShader.setVec3(uniformName, 1.0f, 1.0f, 1.0f);
            sprintf(uniformName, "pointLights[%d].constant", i);
            lightingShader.setFloat(uniformName, 1.0f);
            sprintf(uniformName, "pointLights[%d].linear", i);
            lightingShader.setFloat(uniformName, 0.09f);
            sprintf(uniformName, "pointLights[%d].quadratic", i);
            lightingShader.setFloat(uniformName, 0.032f);
        }
        // emission properties
        lightingShader.setInt("emission", 2);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", glm::value_ptr(projection));
        lightingShader.setMat4("view", glm::value_ptr(view));

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", glm::value_ptr(model));

        // Render crate cubes
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureContainer);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        for(unsigned int i = 1; i < 10; i++)
        {
            glm::mat4 m2 = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            lightingShader.setMat4F("model", 1, GL_FALSE, glm::value_ptr(m2));
            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Render white cubes as lamps
        for (int i = 0; i < 4; i++)
        {
            lightCubeShader.use();
            lightCubeShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
            lightCubeShader.setMat4("projection", glm::value_ptr(projection));
            lightCubeShader.setMat4("view", glm::value_ptr(view));
            model = glm::translate(glm::mat4(1.0f), pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
            lightCubeShader.setMat4("model", glm::value_ptr(model));

            glBindVertexArray(lightCubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

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

unsigned int loadTexture(const char * path)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    // image load texture
    int width, height, nrChannels;
    unsigned char * data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format = GL_RGBA;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // set texture wrapping/filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture!" << std::endl;
        return -1;
    }
    return texture;
}