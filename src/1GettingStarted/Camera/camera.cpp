#include <stdint.h>
#include <iostream>
#include "glad/glad.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/gl.h>

#include <stb/stb_image.h>
#include "src/shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

glm::mat4 customLookAt(glm::vec3 & pos, const glm::vec3 & front, glm::vec3 & up);

//Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
unsigned int indices[] = {
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
    16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
    31,32,33,34,35
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

float floorVertices[] = {
    // vertices             // text coord
    -0.5f, 0.0f, -0.5f,     -1.0f, -1.0f,
    -0.5f, 0.0f, 0.5f,      -1.0f, 1.0f,
    0.5f, 0.0f, 0.5f,       1.0f, 1.0f,
    0.5f, 0.0f, 0.5f,       1.0f, 1.0f,
    -0.5f, 0.0f, -0.5f,     -1.0f, -1.0f,
    0.5f, 0.0f, -0.5f,      1.0f, -1.0f
};

glm::vec3 cameraPos   = glm::vec3(0.0f, 2.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
float cameraSensitivity = 0.1f;
float yaw = -90.0f;
float pitch = 0.0f;


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

    // stbi attributes
    stbi_set_flip_vertically_on_load(true);

    // create our vertex array object
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind VAO
    glBindVertexArray(VAO);

    // create vertex buffer object from 'vertices[]' and 'indices[]'
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // set the vertex colour attribute pointers
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // set texture coord pointers
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    GLuint VAO_floor, VBO_floor;
    glGenVertexArrays(1, &VAO_floor);
    glGenBuffers(1, &VBO_floor);
    glBindVertexArray(VAO_floor);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_floor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAO);

    // compile shaders
    Shader myShader = Shader(
            "src/1GettingStarted/Camera/vertex.vert",
            "src/1GettingStarted/Camera/fragment.frag");
    myShader.use();

    // gl load texture
    unsigned int texture[2];
    glGenTextures(2, texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    // set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // image load texture
    int width, height, nrChannels;
    unsigned char * data = stbi_load("assets/textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        std::cout << "pic: [" << width << ", " << height << "]" << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture!" << std::endl;
    }
    // Texture 2
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    // set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // image load texture
    data = stbi_load("assets/textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        std::cout << "pic: [" << width << ", " << height << "]" << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture!" << std::endl;
    }
    // Texture 3 - GRASS
    glBindVertexArray(VAO_floor);
    unsigned int textureGrass;
    glGenTextures(1, &textureGrass);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureGrass);
    // set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // image load texture
    data = stbi_load("assets/textures/grass.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        std::cout << "pic: [" << width << ", " << height << "]" << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture!" << std::endl;
    }

    // return to default VAO
    glBindVertexArray(VAO);


    // matrix transformations
    glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    // COORD SYSTEMS MATRIX TRANSFORMATIONS
    // model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // --------------------
    // CAMERA
    // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    // glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    // glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    // ---------------------
    // THE HARD WAY
    // glm::mat4 view =
    // {
    //     cameraRight.x, cameraRight.y, cameraRight.z, 0.0f,
    //     cameraUp.x, cameraUp.y, cameraUp.z, 0.0f,
    //     cameraDirection.x, cameraDirection.y, cameraDirection.z, 0.0f,
    //     0.0f, 0.0f, 0.0f, 1.0f
    // };
    // glm::mat4 viewPos =
    // {
    //     1.0, 0.0f, 0.0f, (-1)*cameraPos.x,
    //     0.0, 1.0f, 0.0f, (-1)*cameraPos.y,
    //     0.0, 0.0f, 1.0f, (-1)*cameraPos.z,
    //     0.0, 0.0f, 0.0f, 1.0f
    // };
    // std::cout << glm::to_string(view) << std::endl;
    // std::cout << glm::to_string(viewPos) << std::endl;
    // view = glm::transpose(view) * glm::transpose(viewPos);
    // std::cout << "Right: " << glm::to_string(cameraRight) << std::endl;
    // std::cout << "Up: " << glm::to_string(cameraUp) << std::endl;
    // std::cout << "Direction: " << glm::to_string(cameraDirection) << std::endl;
    // std::cout << "Position: " << glm::to_string(cameraPos) << std::endl;
    // std::cout << glm::to_string(view) << std::endl;
    // ---------------------------------
    // THE EASY WAY
    // glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
    //                     glm::vec3(0.0f, 0.0f, 0.0f),
    //                     glm::vec3(0.0f, 1.0f, 0.0f));
    // std::cout << glm::to_string(view) << std::endl;



    // projection
    float fov = 90.0f;
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);


    // render loop
    int32_t Running = 1;
    int32_t FullScreen = 0;

    bool rotateClockwise = true;
    float curRotation = 0.0f;
    float lastTicks = (float)SDL_GetTicks()/1000;

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
            cameraPos += cameraSpeed * glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z));
        if (keystate[SDL_SCANCODE_S])
            cameraPos -= cameraSpeed * glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z));
        if (keystate[SDL_SCANCODE_A])
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (keystate[SDL_SCANCODE_D])
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

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
                yaw += static_cast<float>(Event.motion.xrel) * cameraSensitivity;
                pitch += static_cast<float>(Event.motion.yrel) * cameraSensitivity * (-1);
                if (pitch > 89.0f)
                    pitch = 89.0f;
                if (pitch < -89.0f)
                    pitch = -89.f;

                glm::vec3 direction;
                direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
                direction.y = sin(glm::radians(pitch));
                direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
                cameraFront = glm::normalize(direction);
            }
            else if (Event.type == SDL_MOUSEWHEEL && SDL_GetRelativeMouseMode() == SDL_TRUE)
            {
                fov -= static_cast<float>(Event.wheel.y) * 5;
                if (fov < 1.0f)
                    fov = 1.0f;
                if (fov >= 90.0f)
                    fov = 90.f;
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

        // Update camera view matrix
        //view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        view = customLookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        // Update camera projection matrix
        projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);

        // render container
        myShader.use();
        myShader.setInt("texture1", 0);
        myShader.setInt("texture2", 1);

        // transformations
        myShader.setMat4F("transform", 1, GL_FALSE, glm::value_ptr(trans));
        glm::mat4 trans2 = glm::mat4(1.0f);
        float diff = (float)SDL_GetTicks() - lastTicks;
        lastTicks = (float)SDL_GetTicks();
        if (rotateClockwise)
            curRotation = remainder(curRotation - diff/1000, 2*3.141592);
        else
            curRotation = remainder(curRotation + diff/1000, 2*3.141592);
        trans2 = glm::rotate(trans2, curRotation, glm::vec3(0.5f, 0.5f, 1.0f));
        myShader.setMat4F("transform", 1, GL_FALSE, glm::value_ptr(trans2));

        // coord system transformations
        myShader.setMat4F("model", 1, GL_FALSE, glm::value_ptr(model));
        myShader.setMat4F("view", 1, GL_FALSE, glm::value_ptr(view));
        myShader.setMat4F("projection", 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        for(unsigned int i = 1; i < 10; i++)
        {
            glm::mat4 m2 = glm::mat4(1.0f);
            m2 = glm::translate(m2, cubePositions[i]);
            myShader.setMat4F("model", 1, GL_FALSE, glm::value_ptr(m2));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Draw the grassy floor
        glBindVertexArray(VAO_floor);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureGrass);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, NULL);
        myShader.use();
        glm::mat4 m2 = glm::mat4(1.0f);
        m2 = glm::scale(m2, glm::vec3(100.0f, 100.0f, 100.0f));
        myShader.setMat4F("model", 1, GL_FALSE, glm::value_ptr(m2));
        myShader.setMat4F("view", 1, GL_FALSE, glm::value_ptr(view));
        myShader.setMat4F("projection", 1, GL_FALSE, glm::value_ptr(projection));
        myShader.setMat4F("transform", 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 6);

        SDL_GL_SwapWindow(Window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    SDL_GL_DeleteContext(Context);
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}

glm::mat4 customLookAt(glm::vec3 & pos, const glm::vec3 & direction, glm::vec3 & up)
{
    glm::vec3 cameraPos = pos;
    glm::vec3 cameraTarget = direction;
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 cameraUp = up;
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);

    glm::mat4 view =
    {
        cameraRight.x, cameraRight.y, cameraRight.z, 0.0f,
        cameraUp.x, cameraUp.y, cameraUp.z, 0.0f,
        cameraDirection.x, cameraDirection.y, cameraDirection.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glm::mat4 viewPos =
    {
        1.0, 0.0f, 0.0f, (-1)*cameraPos.x,
        0.0, 1.0f, 0.0f, (-1)*cameraPos.y,
        0.0, 0.0f, 1.0f, (-1)*cameraPos.z,
        0.0, 0.0f, 0.0f, 1.0f
    };
    // std::cout << glm::to_string(view) << std::endl;
    // std::cout << glm::to_string(viewPos) << std::endl;
    view = glm::transpose(view) * glm::transpose(viewPos);
    // std::cout << "Right: " << glm::to_string(cameraRight) << std::endl;
    // std::cout << "Up: " << glm::to_string(cameraUp) << std::endl;
    // std::cout << "Direction: " << glm::to_string(cameraDirection) << std::endl;
    // std::cout << "Position: " << glm::to_string(cameraPos) << std::endl;
    // std::cout << glm::to_string(view) << std::endl;
    return view;
}
