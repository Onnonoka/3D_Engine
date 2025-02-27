#pragma once

#include <glm/glm.hpp>
#include <Object3D/BasicObject.hpp>
#include <Core/Dirty.hpp>

/**
 * @brief Represents a camera in a 3D scene.
 */
class Camera : public BasicObject, public Dirty {
public:
    
    /**
     * @brief Enum representing dirty fields for camera updates.
     */
    enum DirtyField {
        VIEW = 0,        ///< View matrix
        PROJECTION = 1   ///< Projection matrix
    };

    /**
     * @brief Constructs a Camera object with optional initial position, rotation, and field of view (FOV).
     * @param position The initial position vector.
     * @param rotation The initial rotation vector.
     * @param fov The initial field of view angle in degrees.
     */
    Camera(const glm::vec3 position = glm::vec3(0.0f), const glm::vec3 rotation = glm::vec3(0.0f), const float fov = 90.f);

    /**
     * @brief Sets the field of view (FOV) of the camera.
     * @param newFOV The new field of view angle in degrees.
     */
    void setFOV(const float newFOV);

    /**
     * @brief Retrieves the current field of view (FOV) of the camera.
     * @return The current field of view angle in degrees.
     */
    float getFOV() const;

    /**
     * @brief Retrieves the view matrix of the camera.
     * @return The view matrix.
     */
    glm::mat4 getViewMatrix() const;

    /**
     * @brief Retrieves the projection matrix of the camera.
     * @return The projection matrix.
     */
    glm::mat4 getProjectionMatrix() const;

    /**
     * @brief Sets the screen size for the camera.
     * @param width The width of the screen.
     * @param height The height of the screen.
     */
    void setScreenSize(const float width, const float height);

    /**
     * @brief Sets the position of the camera.
     * @param newPosition The new position vector.
     */
    void setPosition(const glm::vec3 newPosition);

    /**
     * @brief Translates the camera.
     * @param translation The translation vector.
     */
    void translate(const glm::vec3 translation);

    /**
     * @brief Points the camera to look at a specified point.
     * @param point The point to look at.
     */
    void lookAt(const glm::vec3 point);
    
    /**
     * @brief Updates the view matrix based on the camera's current position and orientation.
     */
    void updateViewMatrix();

    /**
     * @brief Updates the projection matrix based on the camera's field of view (FOV) and screen dimensions.
     */
    void updateProjectionMatrix();

    /**
     * @brief Updates the GL uniforms for the camera.
     */
    void updateGLUiniform();

    /**
     * @brief Renders the camera using the specified shader program.
     * @param shaderProgram The shader program to use for rendering.
     */
    void render(GLuint shaderProgram);

private:
    float fov;                                      ///< Field of view angle in degrees
    float screenWidth;                              ///< Width of the screen
    float screenHeight;                             ///< Height of the screen
    
    glm::mat4 viewMatrix = glm::mat4(1.0f);         ///< View matrix of the camera
    glm::mat4 projectionMatrix = glm::mat4(1.0f);   ///< Projection matrix of the camera

    glm::vec3 pointToLook = glm::vec3(0, 0, 0);     ///< Point to look at for camera orientation

};