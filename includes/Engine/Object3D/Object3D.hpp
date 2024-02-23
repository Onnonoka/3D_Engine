#pragma once

#include <Object3D/BasicObject.hpp>
#include <Object3D/Geometry.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include <memory>
#include <string>

/**
 * @brief Represents a 3D object with position, rotation, and scale.
 */
class Object3D : public BasicObject {
public:
    /**
     * @brief Constructs an Object3D with optional initial position, rotation, and scale.
     * @param position The initial position vector.
     * @param rotation The initial rotation vector.
     * @param scale The initial scale vector.
     */
    Object3D(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));

    ~Object3D();

    /**
     * @brief Retrieves the Vertex Array Object ID associated with the object.
     * @return The Vertex Array Object ID.
     */
    GLuint getVAO() const;

    /**
     * @brief Retrieves the geometry of the object.
     * @return The geometry of the object.
     */
    Geometry getGeometry() const;

    /**
     * @brief Sets the geometry of the object.
     * @param newGeometry The new geometry to set.
     */
    void setGeometry(Geometry newGeometry);

    /**
     * @brief Clears OpenGL buffers associated with the object.
     * This function releases resources associated with the Vertex Array, Vertex Buffer, and Element Buffer Objects.
     */
    void clearBuffers();

protected:
    /**
     * @brief Creates OpenGL buffers for the object's geometry data.
     * This function is internally used to generate Vertex Array, Vertex Buffer, and Element Buffer Objects.
     */
    void createGLBuffer();

private:
    GLuint VAO = 0;             ///< The Vertex Array Object ID associated with the object.
    GLuint VBO = 0;             ///< The Vertex Buffer Object ID associated with the object.
    GLuint EBO = 0;             ///< The Element Buffer Object ID associated with the object.

    Geometry geometry;          ///< The geometry data associated with the object.
    // Material material;
};