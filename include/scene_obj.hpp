#ifndef SCENE_OBJ_HPP
#define SCENE_OBJ_HPP

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "motion.hpp"

struct RGBA {
    float red_value, green_value, blue_value, alpha_value;
    RGBA(float r, float g, float b, float a)
        : red_value(r), green_value(g), blue_value(b),
          alpha_value(a) {}
};

class SceneObject {
public:
    
    Shader *shaderProgram;
    glm::mat4 model, child_transform;
    std::vector<std::vector<Motion>> *motion_flow;
    unsigned int surface_num;

    std::vector<SceneObject*> children;

    float rx, ry, rz;
    float tx, ty, tz;

    float red_value, green_value, blue_value, alpha_value;

    SceneObject(float *vertices, Shader *shaderProgram, glm::mat4 model, 
                    glm::mat4 child_transform, std::vector<std::vector<Motion>> *motion_flow, 
                    unsigned int surface_num, RGBA *colors);

    int dfs_draw(glm::mat4 &ptransform, glm::mat4 &view, glm::mat4 &projection, int motion_idx);
    void add_child(SceneObject *child_obj);

private:
    unsigned int VAO;
    int flow_cnt;
    int last_motion;
};

#endif
