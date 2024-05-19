#include <Renderer/MinimalRrenderer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Core/Error/EngineError.hpp>
#include <iostream>

MinimalRenderer::MinimalRenderer(const Color color) 
    : Renderer(color) {
    
    std::string vertexShaderPath = SHADER_PATH + "MinimalShader.vert";
    std::string fragmentShaderPath = SHADER_PATH + "MinimalShader.frag";
    loadShaders(vertexShaderPath, fragmentShaderPath);
    glEnable(GL_DEPTH_TEST);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glClearColor(getBGColor().r, getBGColor().g, getBGColor().b, 1.0f);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void MinimalRenderer::render(Camera& camera, Renderable& object) {
    // Activate the shader program
    glUseProgram(shaderProgram);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR, {std::to_string(static_cast<unsigned int>(shaderProgram))});

    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    // Initialize the position matrix
    glm::mat4 initialPoisiton(1.0f);

    // Update the uniform variables related to the camera
    camera.updateGLUiniform();
    camera.render(shaderProgram);

    // Render the object using the initialized position matrix and the shader program
    object.render(initialPoisiton, *this);
}
