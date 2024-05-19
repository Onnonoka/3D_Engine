#pragma once

#include <string>
#include <glad/glad.h>
// #include <Object3D/Object3D.hpp>
#include <Camera/Camera.hpp>
#include <Core/Renderable.hpp>
#include <Core/Window.hpp>
#include <Core/Color.hpp>

class Object3D;

#define SHADER_PATH std::string("Shaders/")

/**
 * @brief Abstract class defining a Renderer interface for rendering operations.
 */
class Renderer {
public:

    Renderer(const Color color);

    /**
    * @brief Destructor responsible for freeing shader resources.
    * @details Deletes the vertex shader, fragment shader, and shader program IDs.
    */
    ~Renderer();

    /**
     * @brief Sets the background color.
     * @param color The color to set as the background color.
     */
    void setBGColor(const Color color = Color::LightGray);
    
    /**
     * @brief Retrieves the background color.
     * @return The background color.
     */
    Color getBGColor() const;

    const GLuint getProgram() const;

    /**
     * @brief Pure virtual function to render the scene.
     */
    virtual void render(Camera& camera, Renderable& object) = 0;

protected:

    GLuint vertexShader = 0;            ///< Vertex shader ID.
    GLuint fragmentShader = 0;          ///< Fragment shader ID.
    GLuint shaderProgram = 0;           ///< Shader program ID.

    Color bgColor;                      ///< The background color.

    /**
     * @brief Loads and compiles shaders from the specified files, then creates the shader program.
     * @param vertexShaderFile   Path to the vertex shader file.
     * @param fragmentShaderFile Path to the fragment shader file.
     */
    void loadShaders(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

    void addBinding(int enumName, unsigned int bindingPosition, size_t dataSize);

private:

    
};