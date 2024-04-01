#include <Renderer/MinimalRrenderer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Error/EngineError.hpp>
#include <iostream>

MinimalRenderer::MinimalRenderer() {
    std::string vertexShaderPath = SHADER_PATH + "MinimalShader.vert";
    std::string fragmentShaderPath = SHADER_PATH + "MinimalShader.frag";
    loadShaders(vertexShaderPath, fragmentShaderPath);
    glEnable(GL_DEPTH_TEST);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f); // Gris clair (R, G, B)
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void MinimalRenderer::render(const Camera& camera, Object3D& object) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glm::mat4 initialPoisiton(1.0f);
    object.render(camera, initialPoisiton, shaderProgram);
}
