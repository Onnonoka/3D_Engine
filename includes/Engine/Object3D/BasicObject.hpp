#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

/**
 * @brief Represents a 3D object with position, rotation, and scale.
 */
class BasicObject {
public:

    BasicObject(float x, float y, float z);

    /**
     * @brief Constructs an Object3D with optional initial position, rotation, and scale.
     * @param position The initial position vector.
     * @param rotation The initial rotation vector.
     * @param scale The initial scale vector.
     */
    BasicObject(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));

    ~BasicObject();

    // Setters and Getters

    /**
     * @brief Sets the position of the object.
     * @param newPosition The new position vector.
     */
    void setPosition(glm::vec3 newPosition);

    /**
     * @brief Retrieves the current position of the object.
     * @return The position vector.
     */
    glm::vec3 getPosition() const;

    /**
     * @brief Sets the rotation of the object.
     * @param newRotation The new rotation vector.
     */
    void setRotation(glm::vec3 newRotation);

    /**
     * @brief Retrieves the current rotation of the object.
     * @return The rotation vector.
     */
    glm::vec3 getRotation() const;

    /**
     * @brief Sets the scale of the object.
     * @param newScale The new scale vector.
     */
    void setScale(glm::vec3 newScale);

    /**
     * @brief Retrieves the current scale of the object.
     * @return The scale vector.
     */
    glm::vec3 getScale() const;

    // Other utility methods for transformations.

    /**
     * @brief Translates the object by a specified translation vector.
     * @param translation The translation vector.
     */
    void translate(glm::vec3 translation);

    /**
     * @brief Rotates the object by a specified rotation vector.
     * @param rotation The rotation vector.
     */
    void rotate(glm::vec3 rotation);

    /**
     * @brief Scales the object by a specified scaling vector.
     * @param scaling The scaling vector.
     */
    void scaleBy(glm::vec3 scaling);

    /**
     * @brief Retrieves the transformation matrix of the object.
     * @return The transformation matrix.
     */
    glm::mat4 getTransformationMatrix() const;

private:
    glm::vec3 position;                     ///< The position of the object.
    glm::vec3 rotation;                     ///< The rotation of the object.
    glm::vec3 scale;                        ///< The scale of the object.

    glm::mat4 transformationMatrix;         ///< The transformation matrix of the object.

protected:
    /**
     * @brief Creates the transformation matrix for the object based on its position, rotation, and scale.
     */
    void createTransformationMatrix();
};