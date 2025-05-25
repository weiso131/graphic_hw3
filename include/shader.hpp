#ifndef SHADER_H
#define SHADER_H

typedef struct shader {
    unsigned int shader_program;
    unsigned int modelLoc;
    unsigned int viewLoc; //跟攝影機的相對位置
    unsigned int projectionLoc; // 投影
} Shader;

Shader *create_shader(const char **vertexShaderSource, const char **fragmentShader);

#endif