#include <stdint.h>
#include <iostream>
#include "glad/glad.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/gl.h>

#include <stb/stb_image.h>
#include "src/shader.h"
#include "src/camera.h"
#include "src/3Models/DeskModel/LightCube.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "src/Model.h"

//Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

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

    // make sure stb flips our textures
    //stbi_set_flip_vertically_on_load(true);

    // set viewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    // enable z-buffer
    glEnable(GL_DEPTH_TEST);

    // compile shaders
    Shader lightingShader("src/3Models/DeskModel/colors.vert", "src/3Models/DeskModel/colors.frag");
    Shader lightCubeShader("src/3Models/DeskModel/light_cube.vert", "src/3Models/DeskModel/light_cube.frag");

    // load model
    Model backpack("assets/desk/Obj format/Free model Drawer(Final) .obj");
    // create light object
    std::vector<LightCube> lights;
    LightCube light;
    lights.push_back(light);
    LightCube light2;
    light2.Move(glm::vec3(2.0f, 0.0f, -2.0f));
    light2.setDiffuse(glm::vec3(1.0f, 0.0f, 0.0f));
    lights.push_back(light2);


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

        if (keystate[SDL_SCANCODE_UP])
            light.Move(glm::vec3(0.0f, 0.05f, 0.0f));
        if (keystate[SDL_SCANCODE_DOWN])
            light.Move(glm::vec3(0.0f, -0.05f, 0.0f));


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
                    case 'p':
                        lights.at(0).setActive(!lights.at(0).Active());
                        break;
                    case 'o':
                        lights.at(1).setActive(!lights.at(1).Active());
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

        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);
        lightingShader.setFloat("material.shininess", 1.0f);

        // point light properties
        int activeLights = 0;
        for (int i = 0; i < lights.size(); i++)
        {
            LightCube l = lights.at(i);
            if (!l.Active()) continue;
            lightingShader.setVec3("pointLights[" + to_string(activeLights) + "].position", l.Pos().x, l.Pos().y, l.Pos().z);
            lightingShader.setVec3("pointLights[" + to_string(activeLights) + "].ambient", 0.3f, 0.3f, 0.3f);
            lightingShader.setVec3("pointLights[" + to_string(activeLights) + "].diffuse", l.Diffuse().x, l.Diffuse().y, l.Diffuse().z);
            lightingShader.setVec3("pointLights[" + to_string(activeLights) + "].specular", l.Diffuse().x, l.Diffuse().y, l.Diffuse().z);
            lightingShader.setFloat("pointLights[" + to_string(activeLights) + "].constant", 1.0f);
            lightingShader.setFloat("pointLights[" + to_string(activeLights) + "].linear", 0.09f);
            lightingShader.setFloat("pointLights[" + to_string(activeLights) + "].quadratic", 0.032f);
            activeLights++;
        }
        lightingShader.setInt("activeLights", activeLights);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", glm::value_ptr(projection));
        lightingShader.setMat4("view", glm::value_ptr(view));

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", glm::value_ptr(model));

        backpack.Draw(lightingShader);

        for (int i = 0; i < lights.size(); i++) {
            LightCube l = lights.at(i);
            lightCubeShader.use();
            lightCubeShader.setVec3("lightColor", l.Diffuse().x, l.Diffuse().y, l.Diffuse().z);
            lightCubeShader.setMat4("projection", glm::value_ptr(projection));
            lightCubeShader.setMat4("view", glm::value_ptr(view));
            model = glm::translate(glm::mat4(1.0f), l.Pos());
            model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
            lightCubeShader.setMat4("model", glm::value_ptr(model));
            l.Draw();
        }

        SDL_GL_SwapWindow(Window);
    }

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