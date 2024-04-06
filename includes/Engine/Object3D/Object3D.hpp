#pragma once

#include <Object3D/BasicObject.hpp>
#include <Object3D/Geometry.hpp>
#include <Material/Material.hpp>
#include <Object3D/Camera.hpp>
#include <Core/Renderable.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include <memory>
#include <string>

/**
 * @brief Represents a 3D object with position, rotation, and scale.
 */
class Object3D : public BasicObject, public Renderable {
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
    Geometry& getGeometry();

    /**
     * @brief Sets the geometry of the object.
     * @param newGeometry The new geometry to set.
     */
    void setGeometry(const Geometry newGeometry);

    /**
     * @brief Retrieves the material of the object.
     * @return The material of the object.
     */
    Material& getMaterial();

    /**
     * @brief Sets the material of the object.
     * @param newMaterial The new material to set.
     */
    void setMaterial(const Material newMaterial);

    /**
     * @brief Clears OpenGL buffers associated with the object.
     * This function releases resources associated with the Vertex Array, Vertex Buffer, and Element Buffer Objects.
     */
    void clearBuffers();

    /**
     * @brief Updates OpenGL buffers associated with the object if necessary.
     * This function is internally used to update buffers based on changes in geometry or material.
     */
    void updateGLBuffers();

    /**
     * @brief Surcharge de l'opérateur == pour comparer deux objets 3D.
     * @param other L'autre objet 3D à comparer.
     * @return true si les deux objets sont égaux, false sinon.
     */
    bool operator==(const Object3D& other) const;

    /**
     * @brief Renders the object using the specified camera and parent model matrix.
     * 
     * This function renders the object using the provided camera and parent model matrix.
     * 
     * @param camera The camera to use for rendering.
     * @param parentModelMatrix The parent model matrix representing the transformation of the parent object.
     * @param shaderProgram The shader program to use for rendering.
     */
    virtual void render(const glm::mat4 parentModelMatrix, const GLuint shaderProgram) override;

protected:
    /**
     * @brief Creates OpenGL buffers for the object's geometry data.
     * This function is internally used to generate Vertex Array, Vertex Buffer, and Element Buffer Objects.
     */
    void createGLBuffers();

private:

    GLuint VAO = 0;             ///< The Vertex Array Object ID associated with the object.
    GLuint VBO = 0;             ///< The Vertex Buffer Object ID associated with the object.
    GLuint CBO = 0;             ///< The Color Buffer Object ID associated with the object.
    GLuint EBO = 0;             ///< The Element Buffer Object ID associated with the object.

    Geometry geometry;          ///< The geometry data associated with the object.
    Material material;          ///< The material data associated with the object.

};