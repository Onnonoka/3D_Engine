#include <Renderer/MinimalRrenderer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Core/Error/EngineError.hpp>
#include <iostream>

MinimalRenderer::MinimalRenderer() {
    std::string vertexShaderPath = SHADER_PATH + "MinimalShader.vert";
    std::string fragmentShaderPath = SHADER_PATH + "MinimalShader.frag";
    loadShaders(vertexShaderPath, fragmentShaderPath);
    glEnable(GL_DEPTH_TEST);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glClearColor(getBGColor().r, getBGColor().g, getBGColor().b, 1.0f); // Gris clair (R, G, B)
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void MinimalRenderer::render(Camera& camera, Renderable& object) {
    
    glUseProgram(shaderProgram);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR, {std::to_string(static_cast<unsigned int>(shaderProgram))});

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    camera.updateGLUiniform();
    camera.render(shaderProgram);

    glm::mat4 initialPoisiton(1.0f);
    
    object.render(initialPoisiton, shaderProgram);
}
