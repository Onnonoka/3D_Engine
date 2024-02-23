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

void MinimalRenderer::render(const Camera& camera, const Object3D& object) {
    if (vertexShader != 0 && fragmentShader != 0 && shaderProgram != 0) {

        glUseProgram(shaderProgram);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR, {std::to_string(static_cast<unsigned int>(shaderProgram))});

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        glBindVertexArray(object.getVAO());
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

        GLuint transformMatrixLocation = glGetUniformLocation(shaderProgram, "transform");
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "view");
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projection");
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        glUniformMatrix4fv(transformMatrixLocation, 1, GL_FALSE, glm::value_ptr(object.getTransformationMatrix()));
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix()));
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(object.getGeometry().getNumberOfFaces()), GL_UNSIGNED_INT, 0);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
        
        glBindVertexArray(0);
        CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    } else {
        ENGINE_SKIP_IMPLEMENTATION_ERROR(GET_CTX_ERROR, RenderError::RENDERER_NOT_INITIALIZED);
    }
}