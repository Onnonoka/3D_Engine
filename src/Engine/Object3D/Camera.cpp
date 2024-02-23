#include <Object3D/Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 rotation, float fov)
    : BasicObject(position, rotation, glm::vec3(1.0f)), fov(fov) {
    updateProjectionMatrix();
    updateViewMatrix();
}

void Camera::setFOV(float newFOV) {
    fov = newFOV;
    updateProjectionMatrix();
}

float Camera::getFOV() const {
    return fov;
}

void Camera::setScreenSize(float width, float height) {
    screenWidth = width;
    screenHeight = height;
    updateProjectionMatrix();
}

glm::mat4 Camera::getViewMatrix() const {
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

void Camera::updateViewMatrix() {
    glm::vec3 direction = glm::vec3(
        cos(glm::radians(getRotation().y)) * cos(glm::radians(getRotation().x)),
        sin(glm::radians(getRotation().x)),
        sin(glm::radians(getRotation().y)) * cos(glm::radians(getRotation().x))
    );
    glm::vec3 pointToLook = getPosition() + direction;
    viewMatrix = glm::lookAt(getPosition(), pointToLook, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::updateProjectionMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fov), screenWidth / screenHeight, 0.1f, 100.0f);
}

void Camera::setRotation(glm::vec3 newRotation) {
    BasicObject::setRotation(newRotation);
    updateViewMatrix();
}

void Camera::setPosition(glm::vec3 newPosition) {
    BasicObject::setPosition(newPosition);
    updateViewMatrix();
}

void Camera::rotate(glm::vec3 rotation) {
    BasicObject::rotate(rotation);
    updateViewMatrix();
}

void Camera::translate(glm::vec3 translation) {
    BasicObject::translate(translation);
    updateViewMatrix();
}


