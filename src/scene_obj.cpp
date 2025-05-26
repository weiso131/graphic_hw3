#include "scene_obj.hpp"

#include <iostream>
#define update_macro(parameter) {\
    this->parameter = (*this->motion_flow)[motion_idx][flow_cnt].parameter;\
}

SceneObject::SceneObject(float *vertices, Shader *shaderProgram, glm::mat4 model,
                    glm::mat4 child_transform, std::vector<std::vector<Motion>> *motion_flow, unsigned int surface_num) {
    
    unsigned int VBO;
        
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, surface_num * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->shaderProgram = shaderProgram;
    this->model = model;
    this->child_transform = child_transform;
    this->motion_flow = motion_flow;
    this->surface_num = surface_num;

    this->rx = this->ry = this->rz = this->tx = this->ty = this->tz = 0.0f;
    this->last_motion = DO_NOTHING;
    this->flow_cnt = this->speed_cnt = 0;
}

void SceneObject::dfs_draw(glm::mat4 &ptransform, glm::mat4 &view, \
glm::mat4 &projection, int motion_idx) {
    Shader *ShaderProgram = this->shaderProgram;
    glBindVertexArray(this->VAO);
    glUseProgram(ShaderProgram->shader_program);


    if (motion_idx != this->last_motion) {
        this->flow_cnt = this->speed_cnt = 0;
        this->last_motion = motion_idx;
    } 
    if (motion_idx != DO_NOTHING) {
        update_macro(rx);
        update_macro(ry);
        update_macro(rz);
        update_macro(tx);
        update_macro(ty);
        update_macro(tz);

        this->flow_cnt++;
        if (this->flow_cnt == (*this->motion_flow)[motion_idx].size()) {
            this->flow_cnt--;
            //Todo: 可能要告知使用者動作完成了
        }
            
    }
        
    glm::mat4 world_model, self_model;
    glm::mat4 translate_mat = glm::translate(glm::mat4(1.0f), glm::vec3(this->tx, this->ty, this->tz));
    glm::mat4 rotate_mat = glm::rotate(glm::mat4(1.0f), glm::radians(this->rx), glm::vec3(1.0f, 0.0f, 0.0f));
    rotate_mat = glm::rotate(rotate_mat, glm::radians(this->ry), glm::vec3(0.0f, 1.0f, 0.0f));
    rotate_mat = glm::rotate(rotate_mat, glm::radians(this->rz), glm::vec3(0.0f, 0.0f, 1.0f));

    world_model = ptransform * this->child_transform * translate_mat * rotate_mat;
    self_model = world_model * this->model;

    glUniformMatrix4fv(ShaderProgram->viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(ShaderProgram->projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(ShaderProgram->modelLoc, 1, GL_FALSE, glm::value_ptr(self_model));
    
    glDrawArrays(GL_TRIANGLES, 0, this->surface_num);
    glBindVertexArray(0);
    glUseProgram(0);

    for (SceneObject *child_obj : this->children) 
        child_obj->dfs_draw(world_model, view, projection, motion_idx);
}

void SceneObject::add_child(SceneObject *child_obj) {
    this->children.push_back(child_obj);
}