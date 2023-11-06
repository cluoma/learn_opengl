#include <stdint.h>
#include <iostream>
#include "glad/glad.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/gl.h>

// function definitions
bool checkShaderCompile(GLuint shader);
bool checkShaderProgramCompile(GLuint shaderProgram);

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

float vertices[] = {
        // tri 1
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
};
float vertices2[] = {
        // tri 2
        0.5f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
        0.75f, 0.5f, 0.0f
};

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}";
const char *fragmentShaderSourceYellow = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
                                   "}";


void processInput(SDL_Event &Event) {

}

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

    // create our vertex array object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // create vertex buffer object from 'vertices[]'
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // create our vertex array object
    GLuint VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    // create vertex buffer object from 'vertices[]'
    GLuint VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    // set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // compile vertex shader
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    if (!checkShaderCompile(vertexShader)) {
        return -1;
    }

    // compile fragment shader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    if (!checkShaderCompile(fragmentShader)) {
        return -1;
    }

    // compile fragment shader yellow
    GLuint fragmentShaderYellow;
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
    glCompileShader(fragmentShaderYellow);
    if (!checkShaderCompile(fragmentShaderYellow)) {
        return -1;
    }

    // create shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    if (!checkShaderProgramCompile(shaderProgram)) {
        return -1;
    }

    // create shader program yellow
    GLuint shaderProgramYellow;
    shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);
    if (!checkShaderProgramCompile(shaderProgramYellow)) {
        return -1;
    }

    // cleanup shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // use our shader program
    glUseProgram(shaderProgram);


    // render loop
    int32_t Running = 1;
    int32_t FullScreen = 0;
    while (Running)
    {
        SDL_Event Event;
        processInput(Event);
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
            else if (Event.type == SDL_WINDOWEVENT)
            {
                if(Event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    std::cout << "window resized: [" << Event.window.data1 << ", " << Event.window.data2 << "]" << std::endl;
                    glViewport(0, 0, Event.window.data1, Event.window.data2);
                }
            }
            else if (Event.type == SDL_QUIT)
            {
                Running = 0;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // tri 1
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // tri 2
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(Window);
    }

    return 0;
}

bool checkShaderCompile(GLuint shader) {
    // check it was compiled successfully
    GLint  success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}

bool checkShaderProgramCompile(GLuint shaderProgram) {
    // check it was compiled successfully
    GLint  success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}
