//
// Created by colin on 12/23/23.
//

#ifndef LEARNOGL_LIGHTCUBE_H
#define LEARNOGL_LIGHTCUBE_H

#include <src/shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

class LightCube {

public:
    LightCube();
    //~LightCube();
    void Draw() const;

    glm::vec3 Pos();
    glm::vec3 Diffuse();
    void Move(glm::vec3 v);
    [[nodiscard]] bool Active() const;
    void setDiffuse(glm::vec3 v);
    void setActive(bool a);

private:
    glm::vec3 Pos_;
    glm::vec3 Diffuse_;
    unsigned int VAO, VBO, EBO;
    bool isOn;

    glm::vec3 InactiveColor = glm::vec3(0.1f, 0.1f, 0.1f);
};


#endif //LEARNOGL_LIGHTCUBE_H
