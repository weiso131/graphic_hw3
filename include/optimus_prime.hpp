#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "scene_obj.hpp"
#include "motion.hpp"
#include "shader.hpp"

#define add_motion(target, n, index, rx, ry, rz, tx, ty, tz) {\
    for (int i = 1;i < n;i++) {\
        float _rx = rx * (float)(i) / (float)n;\
        float _ry = ry * (float)(i) / (float)n;\
        float _rz = rz * (float)(i) / (float)n;\
        float _tx = tx * (float)(i) / (float)n;\
        float _ty = ty * (float)(i) / (float)n;\
        float _tz = tz * (float)(i) / (float)n;\
        (*target)[index].push_back(Motion(_rx, _ry, _rz, _tx, _ty, _tz));\
    }\
    (*target)[index].push_back(Motion(rx, ry, rz, tx, ty, tz));\
}

#define add_motion_reverse(target, n, index, rx, ry, rz, tx, ty, tz) {\
    for (int i = n - 1;i > 0;i--) {\
        float _rx = rx * (float)(i) / (float)n;\
        float _ry = ry * (float)(i) / (float)n;\
        float _rz = rz * (float)(i) / (float)n;\
        float _tx = tx * (float)(i) / (float)n;\
        float _ty = ty * (float)(i) / (float)n;\
        float _tz = tz * (float)(i) / (float)n;\
        (*target)[index].push_back(Motion(_rx, _ry, _rz, _tx, _ty, _tz));\
    }\
    (*target)[index].push_back(Motion(0, 0, 0, 0, 0, 0));\
}


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

static SceneObject *generate_transformer(Shader *global_shader)
{
    RGBA *main_body_color = new RGBA(0.7f, 0.0f, 0.0f, 0.3f);
    RGBA *head_color = new RGBA(0.0f, 0.0f, 0.7f, 0.3f);
    RGBA *metal_gray_color = new RGBA(0.7f, 0.7f, 0.7f, 0.3f);
    // 主身體
    glm::mat4 main_body_model = glm::mat4(1.0f);
    main_body_model = glm::scale(main_body_model, glm::vec3(9.0f, 5.0f, 4.0f));
    auto* main_body_motion = new std::vector<std::vector<Motion>> {
        {Motion(0.0f, 0.0, 0.0, 0.0, 0.0, 0.0)},
        {Motion(0.0f, 0.0, 0.0, 0.0, 0.0, 0.0)}
    };
    SceneObject *main_body = new SceneObject(vertices, global_shader, main_body_model, \
                            glm::mat4(1.0f), main_body_motion, 36, main_body_color);

    //頭
    glm::mat4 head_model = glm::mat4(1.0f);
    head_model = glm::scale(head_model, glm::vec3(3.0f, 3.0f, 3.0f));
    glm::mat4 head_tc = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 4.0f, 0.0f));
    auto* head_motion = new std::vector<std::vector<Motion>> {
        {},
        {}
    };
    add_motion(head_motion, 100, 0, 0, 0, 0, 0, -4.0f, 0);
    add_motion_reverse(head_motion, 100, 1, 0, 0, 0, 0, -4.0f, 0);

    SceneObject *head = new SceneObject(vertices, global_shader, head_model, head_tc, head_motion, 36, head_color);
    main_body->add_child(head);

    //腰部
    glm::mat4 waist_model = glm::mat4(1.0f);
    waist_model = glm::scale(waist_model, glm::vec3(7.0f, 4.0f, 3.0f));
    glm::mat4 waist_tc = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -4.5f, 0.0f));
    auto* waist_motion = new std::vector<std::vector<Motion>>{
        {},
        {}
    };
    add_motion(waist_motion, 100, 0, 0, 0, 0, 0, 1.5f, 0.4f);
    add_motion_reverse(waist_motion, 100, 1, 0, 0, 0, 0, 1.5f, 0.4f);

    SceneObject *waist = new SceneObject(vertices, global_shader, waist_model, waist_tc, waist_motion, 36, metal_gray_color);   
    main_body->add_child(waist);

    //腹部
    glm::mat4 abdomen_model = glm::mat4(1.0f);
    abdomen_model = glm::scale(abdomen_model, glm::vec3(6.0f, 2.0f, 3.0f));
    glm::mat4 abdomen_ct = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
    auto* abdomen_motion = new std::vector<std::vector<Motion>>{
        {},
        {}
    };
    add_motion(abdomen_motion, 100, 0, 90, 180, 0, 0, 2.5f, -2.5f);
    add_motion_reverse(abdomen_motion, 100, 1, 90, 180, 0, 0, 2.5f, -2.5f);

    SceneObject *abdomen = new SceneObject(vertices, global_shader, abdomen_model, abdomen_ct, abdomen_motion, 36, metal_gray_color);
    waist->add_child(abdomen);

    //手臂模型
    glm::mat4 arm_model = glm::mat4(1.0f);
    arm_model = glm::translate(arm_model, glm::vec3(0.0f, -2.75f, 0.0f));
    arm_model = glm::scale(arm_model, glm::vec3(2.5f, 6.5f, 2.5f));

    //左手臂
    // arm 1
    glm::mat4 left_arm1_tc = glm::translate(glm::mat4(1.0f), glm::vec3(5.75f, 2.0f, 0.0f));
    auto* left_arm1_motion = new std::vector<std::vector<Motion>>{
        {},
        {}
    };

    add_motion(left_arm1_motion, 100, 0, 0, 0, 0, -2.5f, 0, -3.25f);
    add_motion_reverse(left_arm1_motion, 100, 1, 0, 0, 0, -2.5f, 0, -3.25f);

    SceneObject *left_arm1 = new SceneObject(vertices, global_shader, arm_model, left_arm1_tc, left_arm1_motion, 36, main_body_color);
    main_body->add_child(left_arm1);

    // arm 2
    glm::mat4 left_arm2_tc = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -6.0f, 0.0f));
    auto* left_arm2_motion = new std::vector<std::vector<Motion>>{
        {},
        {}
    };

    add_motion(left_arm2_motion, 100, 0, -90.0f, 0, 0, 0, 0.25f, -0.75f);
    add_motion_reverse(left_arm2_motion, 100, 1, -90.0f, 0, 0, 0, 0.25f, -0.75f);

    SceneObject *left_arm2 = new SceneObject(vertices, global_shader, arm_model, left_arm2_tc, left_arm2_motion, 36, main_body_color);
    left_arm1->add_child(left_arm2);

    //右手臂
    // arm 1
    
    glm::mat4 right_arm1_tc = glm::translate(glm::mat4(1.0f), glm::vec3(-5.75f, 2.0f, 0.0f));
    auto* right_arm1_motion = new std::vector<std::vector<Motion>>{
        {},
        {}
    };
    add_motion(right_arm1_motion, 100, 0, 0, 0, 0, 2.5f, 0, -3.25f);
    add_motion_reverse(right_arm1_motion, 100, 1, 0, 0, 0, 2.5f, 0, -3.25f);

    SceneObject *right_arm1 = new SceneObject(vertices, global_shader, arm_model, right_arm1_tc, right_arm1_motion, 36, main_body_color);
    main_body->add_child(right_arm1);

    // arm 2
    glm::mat4 right_arm2_tc = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -6.0f, 0.0f));
    auto* right_arm2_motion = new std::vector<std::vector<Motion>>{
        {},
        {}
    };

    add_motion(right_arm2_motion, 100, 0, -90.0f, 0, 0, 0, 0.25f, -0.75f);
    add_motion_reverse(right_arm2_motion, 100, 1, -90.0f, 0, 0, 0, 0.25f, -0.75f);

    SceneObject *right_arm2 = new SceneObject(vertices, global_shader, arm_model, right_arm2_tc, right_arm2_motion, 36, main_body_color);
    right_arm1->add_child(right_arm2);


    //leg 1 模型
    glm::mat4 leg1_model = glm::mat4(1.0f);
    leg1_model = glm::translate(leg1_model, glm::vec3(0.0f, -3.5f, 0.0f));
    leg1_model = glm::scale(leg1_model, glm::vec3(2.5f, 7.0f, 2.5f));

    //leg 1 動作
    auto* leg1_motion = new std::vector<std::vector<Motion>>{
        {},
        {}
    };
    add_motion(leg1_motion, 100, 0, 0, 0, 0, 0, 0, -0.25f);
    add_motion_reverse(leg1_motion, 100, 1, 0, 0, 0, 0, 0, -0.25f);

    //leg 2 模型
    glm::mat4 leg2_model = glm::mat4(1.0f);
    leg2_model = glm::translate(leg2_model, glm::vec3(0.0f, -3.5f, 0.0f));
    leg2_model = glm::scale(leg2_model, glm::vec3(3.0f, 8.0f, 3.0f));

    
    //左腿
    //leg1
    glm::mat4 left_leg1_tc = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -1.0f, 0.0f));
    SceneObject *left_leg1 = new SceneObject(vertices, global_shader, leg1_model, left_leg1_tc, leg1_motion, 36, metal_gray_color);
    abdomen->add_child(left_leg1);

    //leg2
    glm::mat4 left_leg2_tc = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -6.5f, 0.0f));

    auto* left_leg2_motion = new std::vector<std::vector<Motion>>{
        {},
        {}
    };
    add_motion(left_leg2_motion, 100, 0, 0, 0, 0, 1.0f, 3.0f, 0);
    add_motion_reverse(left_leg2_motion, 100, 1, 0, 0, 0, 1.0f, 3.0f, 0);

    SceneObject *left_leg2 = new SceneObject(vertices, global_shader, leg2_model, left_leg2_tc, left_leg2_motion, 36, head_color);
    left_leg1->add_child(left_leg2);

    //右腿
    //leg1
    glm::mat4 right_leg1_tc = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, -1.0f, 0.0f));
    SceneObject *right_leg1 = new SceneObject(vertices, global_shader, leg1_model, right_leg1_tc, leg1_motion, 36, metal_gray_color);
    abdomen->add_child(right_leg1);

    //leg2
    glm::mat4 right_leg2_tc = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25f, -6.5f, 0.0f));

    auto* right_leg2_motion = new std::vector<std::vector<Motion>>{
        {},
        {}
    };
    add_motion(right_leg2_motion, 100, 0, 0, 0, 0, -1.0f, 3.0f, 0);
    add_motion_reverse(right_leg2_motion, 100, 1, 0, 0, 0, -1.0f, 3.0f, 0);

    SceneObject *right_leg2 = new SceneObject(vertices, global_shader, leg2_model, right_leg2_tc, right_leg2_motion, 36, head_color);
    right_leg1->add_child(right_leg2);

    return main_body;
}


