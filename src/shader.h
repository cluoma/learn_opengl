//
// Created by colin on 11/8/23.
//

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int id;

    Shader(const char *vertexPath, const char *fragmentPath)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // open shader source files
        vShaderFile.open(vertexPath);
        if (vShaderFile.fail())
        {
            std::cout << "Could not open vertex shader source file" << std::endl;
            std::abort();
        }
        fShaderFile.open(fragmentPath);
        if (fShaderFile.fail())
        {
            std::cout << "Could not open fragment shader source file" << std::endl;
            std::abort();
        }
        // read files into streams
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close files
        vShaderFile.close();
        fShaderFile.close();
        // convert streams to strings
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        const char * vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // compile vertex shader
        unsigned int vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        if (!checkCompileError(vertex, SHADER_VERTEX)) {
            std::abort();
        }
        // compile fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        if (!checkCompileError(fragment, SHADER_FRAGEMENT)) {
            std::abort();
        }
        // link shader program
        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        if (!checkCompileError(id, SHADER_PROGRAM)) {
            std::abort();
        }

        // cleanup shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use()
    {
        glUseProgram(id);
    }
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

private:
    enum compileStep {
        SHADER_VERTEX = 0,
        SHADER_FRAGEMENT,
        SHADER_PROGRAM
    };

    bool checkCompileError(GLuint shader, compileStep step) {
        // check it was compiled successfully
        GLint  success;
        GLchar infoLog[512];
        if (step == SHADER_PROGRAM)
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
                return false;
            }
        }
        else
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
                return false;
            }
        }

        return true;
    }
};

#endif //SHADER_H
