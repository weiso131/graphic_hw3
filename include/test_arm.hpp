#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "scene_obj.hpp"
#include "motion.hpp"
#include "shader.hpp"

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

static SceneObject *generate_arm(Shader *global_shader)
{
    auto* arm1_motion = new std::vector<std::vector<Motion>> {
        {},
    };

    for (int i = 0;i < 360;i++) {
        (*arm1_motion)[0].push_back(Motion(i * 1.0f, 0.0, 0.0, 0.0, 0.0, 0.0));
    }
        

    glm::mat4 arm1_model = glm::mat4(1.0f);
    arm1_model = glm::translate(arm1_model, glm::vec3(0.0f, -1.0f, 0.0f));
    arm1_model = glm::scale(arm1_model, glm::vec3(0.5f, 2.0f, 0.5f));

    glm::mat4 arm1_tc = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    SceneObject *arm1 = new SceneObject(vertices, global_shader, arm1_model, arm1_tc, arm1_motion, 36);

    glm::mat4 arm2_model = glm::mat4(1.0f);
    arm2_model = glm::rotate(arm2_model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    arm2_model = glm::translate(arm2_model, glm::vec3(0.0f, -1.0f, 0.0f));
    arm2_model = glm::scale(arm2_model, glm::vec3(0.5f, 2.0f, 0.5f));
    
    auto* arm2_motion = new std::vector<std::vector<Motion>> {
        {},
    };

    for (int i = 0;i < 360;i++) {
        (*arm2_motion)[0].push_back(Motion(-i * 1.0f, 0.0, 0.0, 0.0, 0.0, 0.0));
    }

    glm::mat4 arm2_tc = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));

    SceneObject *arm2 = new SceneObject(vertices, global_shader, arm2_model, arm2_tc, arm2_motion, 36);

    auto* arm3_motion = new std::vector<std::vector<Motion>>{
        {},
    };

    for (int i = 0;i < 360;i++) {
        (*arm3_motion)[0].push_back(Motion(i * 1.0f, 0.0, 0.0, 0.0, 0.0, 0.0));
    }

    glm::mat4 arm3_model = glm::mat4(1.0f);
    arm3_model = glm::rotate(arm3_model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    arm3_model = glm::translate(arm3_model, glm::vec3(0.0f, -1.0f, 0.0f));
    arm3_model = glm::scale(arm3_model, glm::vec3(0.5f, 2.0f, 0.5f));

    glm::mat4 arm3_tc = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));
    
    SceneObject *arm3 = new SceneObject(vertices, global_shader, arm3_model, arm3_tc, arm3_motion, 36);

    arm1->add_child(arm2);
    arm1->add_child(arm3);



    return arm1;
}


