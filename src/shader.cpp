#include <iostream>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

unsigned int compile_shader(const char **src, int src_num, unsigned int shader_type)
{
    unsigned int shader_id =  glCreateShader(shader_type);

    glShaderSource(shader_id, src_num, src, NULL);// 第二個參數決定 src 的字串數量
    glCompileShader(shader_id);

    int success;
    char infoLog[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    return shader_id;
}

unsigned int link_shader(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) 
        return -1;
    return shaderProgram;
}

Shader *create_shader(const char **vertexShaderSource, const char **fragmentShaderSourece)
{
    unsigned int vertexShader = compile_shader(vertexShaderSource, 1, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compile_shader(fragmentShaderSourece, 1, GL_FRAGMENT_SHADER);

    Shader *shader = (Shader*)malloc(sizeof(Shader));
    unsigned int shaderProgram = link_shader(vertexShader, fragmentShader);
    shader->shader_program = shaderProgram;
    shader->modelLoc = glGetUniformLocation(shaderProgram, "model");
    shader->viewLoc = glGetUniformLocation(shaderProgram, "view");
    shader->projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    shader->colorsLoc = glGetUniformLocation(shaderProgram, "ourColor");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}