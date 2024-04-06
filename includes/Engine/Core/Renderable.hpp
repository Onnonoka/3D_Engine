#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

class Renderable {
public:
    virtual void render(const glm::mat4 parentModelMatrix, const GLuint shaderProgram) = 0;
};