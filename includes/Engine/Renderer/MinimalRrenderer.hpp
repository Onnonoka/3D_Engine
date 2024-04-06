#pragma once

#include <Renderer/Renderer.hpp>

/**
 * @brief Represents a minimal renderer inheriting properties from the Renderer class.
 */
class MinimalRenderer : public Renderer {
public:
    /**
     * @brief Constructs a MinimalRenderer object.
     * 
     * Initializes a MinimalRenderer object for rendering operations.
     */
    MinimalRenderer();

    /**
     * @brief Renders a 3D object using the provided camera and object.
     * 
     * This function renders a given 3D object within the scene using the specified camera.
     * It overrides the render function defined in the base Renderer class.
     * 
     * @param camera The camera object defining the view and projection matrices.
     * @param object The Object3D object to be rendered.
     */
    void render(Camera& camera, Renderable& object) override;

};