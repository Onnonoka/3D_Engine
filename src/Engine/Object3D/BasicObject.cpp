#include <Object3D/BasicObject.hpp>
#include <Basic/Color.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>


BasicObject::BasicObject(float x, float y, float z) 
    : BasicObject(glm::vec3(x, y, z)) {

}

BasicObject::BasicObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale) {
        createTransformationMatrix();
    }

BasicObject::~BasicObject() { }

void BasicObject::setPosition(glm::vec3 newPosition) {
    position = newPosition;
    createTransformationMatrix();
}

glm::vec3 BasicObject::getPosition() const {
    return position;
}

void BasicObject::setRotation(glm::vec3 newRotation) {
    rotation = newRotation;
    createTransformationMatrix();
}

glm::vec3 BasicObject::getRotation() const {
    return rotation;
}

void BasicObject::setScale(glm::vec3 newScale) {
    scale = newScale;
    createTransformationMatrix();
}

glm::vec3 BasicObject::getScale() const {
    return scale;
}

void BasicObject::translate(glm::vec3 translation) {
    position += translation;
    createTransformationMatrix();
}

void BasicObject::rotate(glm::vec3 newRotation) {
    rotation += newRotation;

    // Normalization of rotations to stay within the valid range (0 to 2π radians).
    if (rotation.x >= 360 || rotation.x <= -360) {
        rotation.x = static_cast<float>(fmod(rotation.x, 360));
    }
    if (rotation.y >= 360 || rotation.y <= -360) {
        rotation.y = static_cast<float>(fmod(rotation.y, 360));
    }
    if (rotation.z >= 360 || rotation.z <= -360) {
        rotation.z = static_cast<float>(fmod(rotation.y, 360));
    }

    createTransformationMatrix();
}

void BasicObject::scaleBy(glm::vec3 scaling) {
    scale *= scaling;
    createTransformationMatrix();
}

glm::mat4 BasicObject::getTransformationMatrix() const {
    return transformationMatrix;
}

void BasicObject::createTransformationMatrix() {
    // Build identity matrixe
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, position);

    transformationMatrix = model;
}