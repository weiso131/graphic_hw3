#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "scene_obj.hpp"
#include "motion.hpp"
#include "optimus_prime.hpp"

#define WIDTH 1920
#define HEIGHT 1090

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

glm::mat4 camera(GLFWwindow* window, float &model_rx, float &model_ry, float &dis_x, float &dis_y, float &dis_z) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
        model_rx -= 1.0f;

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        model_rx += 1.0f;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
        model_ry -= 1.0f;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        model_ry += 1.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        dis_z += 0.5f;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        dis_z -= 0.5f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        dis_x += 0.5f;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        dis_x -= 0.5f;
    
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        dis_y -= 0.5f;

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        dis_y += 0.5f;
    glm::mat4 world_transform = glm::mat4(1.0f); 
    
    world_transform = glm::translate(world_transform, glm::vec3(dis_x, dis_y, dis_z));
    world_transform = glm::rotate(world_transform, glm::radians(model_ry), glm::vec3(0.0f, 1.0f, 0.0f));
    world_transform = glm::rotate(world_transform, glm::radians(model_rx), glm::vec3(1.0f, 0.0f, 0.0f));
    
    world_transform = glm::scale(world_transform, glm::vec3(0.25f, 0.25f, 0.25f));

    return world_transform;
}


int main() {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
    
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
    
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
    
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
    
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
    
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
    
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
    "}\n";

    const char *fragmentShaderSourece = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 1.0f, 1.0f, 0.9f);\n"
    "}\n";

    // 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 設定 OpenGL 版本為 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 建立視窗
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Test", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader *global_shader = create_shader(&vertexShaderSource, &fragmentShaderSourece);

    glm::mat4 view            = glm::mat4(1.0f);
    glm::mat4 projection      = glm::mat4(1.0f);
    glm::mat4 model           = glm::mat4(1.0f);
    glm::mat4 child_transform = glm::mat4(1.0f);
    SceneObject *transformer_obj = generate_transformer(global_shader);

    

    glEnable(GL_DEPTH_TEST);
    
    
    
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    float model_rx = 0.0f, model_ry = 0.0f, dis_x = 0.0f, dis_y = 0.0f, dis_z = 0.0f;
    bool animation_lock = false;
    int motion_choice = DO_NOTHING, transform = 0;
    // 主迴圈
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        glm::mat4 world_transform = camera(window, model_rx, model_ry, dis_x, dis_y, dis_z);

        if (!animation_lock) {
            if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
                motion_choice = transform;
                transform ^= 1;
            }
        }

        int not_complete_num = transformer_obj->dfs_draw(world_transform, view, projection, motion_choice);

        if (not_complete_num == 0) {
            animation_lock = false;
            motion_choice = DO_NOTHING;
        }
        else
            animation_lock = true;

        processInput(window);
        // 換 buffer & 處理事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
