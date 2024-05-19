#pragma once

// #include <Renderer/Renderer.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Renderer;

/**
 * @brief Abstract class representing a renderable object.
 *
 * The Renderable class is an abstract class that defines an interface
 * for objects that can be rendered in a scene. Derived classes must
 * implement the render() method to perform rendering of the object using
 * the specified parent model matrix and shader program.
 */
class Renderable {
public:
    /**
     * @brief Renders the object.
     * @param parentModelMatrix The parent model matrix for the object.
     * @param shaderProgram The shader program to use for rendering.
     *
     * This method is pure virtual and must be implemented by derived classes.
     * It performs rendering of the object using the specified parent model
     * matrix and shader program.
     */
    virtual void render(const glm::mat4 parentModelMatrix, const Renderer& renderer) = 0;
};