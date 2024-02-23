#pragma once

#include <Object3D/Object3D.hpp>
#include <vector>

/**
 * @brief Represents a cube object in a 3D space inheriting properties from Object3D.
 * 
 * This class defines a cube object with specified position, rotation, and scale,
 * inheriting from the Object3D class which provides fundamental 3D object properties.
 * Default values for position, rotation, and scale are set if not specified.
 */
class Cube : public Object3D {
public:
    /**
     * @brief Constructs a Cube object with optional initial position, rotation, and scale.
     * @param position The initial position vector.
     * @param rotation The initial rotation vector.
     * @param scale The initial scale vector.
     */
    Cube(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
};
