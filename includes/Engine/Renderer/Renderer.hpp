#pragma once

#include <string>
#include <glad/glad.h>
#include <Object3D/Object3D.hpp>
#include <Object3D/Camera.hpp>
#include <Basic/Window.hpp>

#define SHADER_PATH std::string("Engine/Shaders/")

/**
 * @brief Abstract class defining a Renderer interface for rendering operations.
 */
class Renderer {
public:
    /**
     * @brief Pure virtual function to render the scene.
     */
    virtual void render(const Camera& camera, Object3D& object) = 0;

    /**
    * @brief Destructor responsible for freeing shader resources.
    * @details Deletes the vertex shader, fragment shader, and shader program IDs.
    */
    ~Renderer();

protected:

    GLuint vertexShader = 0;    ///< Vertex shader ID.
    GLuint fragmentShader = 0;  ///< Fragment shader ID.
    GLuint shaderProgram = 0;   ///< Shader program ID.

    /**
     * Loads and compiles shaders from the specified files, then creates the shader program.
     * @param vertexShaderFile   Path to the vertex shader file.
     * @param fragmentShaderFile Path to the fragment shader file.
     */
    void loadShaders(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
};