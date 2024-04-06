#include <Camera/Camera.hpp>
#include <Core/Error/EngineError.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera(const glm::vec3 position, const glm::vec3 rotation, const float fov)
    : BasicObject(position, rotation, glm::vec3(1.0f)), fov(fov) {
    makeDirty(PROJECTION);
    makeDirty(VIEW);
}

void Camera::setFOV(const float newFOV) {
    fov = newFOV;
    makeDirty(PROJECTION);
}

float Camera::getFOV() const {
    return fov;
}

void Camera::setScreenSize(const float width, const float height) {
    screenWidth = width;
    screenHeight = height;
    makeDirty(PROJECTION);
}

glm::mat4 Camera::getViewMatrix() const {
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt(getPosition(), pointToLook, glm::vec3(0.0f, 0.0f, 1.0f));
    cleanDirtyFlag(VIEW);
}

void Camera::updateProjectionMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fov), screenWidth / screenHeight, 0.1f, 100.0f);
    cleanDirtyFlag(PROJECTION);
}

void Camera::setPosition(const glm::vec3 newPosition) {
    BasicObject::setPosition(newPosition);
    makeDirty(VIEW);
}

void Camera::translate(const glm::vec3 translation) {
    BasicObject::translate(translation);
    makeDirty(VIEW);
}

void Camera::lookAt(const glm::vec3 point) {
    pointToLook = point;
    makeDirty(VIEW);
}

void Camera::updateGLUiniform() {
    
    if (isDirty(Camera::PROJECTION)) {
        updateProjectionMatrix();
    }
    
    if (isDirty(Camera::VIEW)) {
        updateViewMatrix();
    }
}

void Camera::render(GLuint shaderProgram) {
    
    GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "view");
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projection");
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(getViewMatrix()));
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(getProjectionMatrix()));
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}
