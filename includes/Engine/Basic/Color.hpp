#pragma once

#include <glm/glm.hpp>

/**
 * @brief Represents an RGB color with floating-point components for red, green, and blue.
 */
class Color : public glm::vec3 {
public:
    /**
     * @brief Constructor for an RGB color.
     * @param red Red component value (between 0.0 and 1.0).
     * @param green Green component value (between 0.0 and 1.0).
     * @param blue Blue component value (between 0.0 and 1.0).
     */
    Color(float red, float green, float blue) : glm::vec3(red, green, blue) {}

    /**
     * @brief Constructeur par défaut initialisant la couleur à noir par défaut.
     */
    Color() : glm::vec3(0.0f, 0.0f, 0.0f) {}

    // Definition of basic colors
    static const Color Red;     ///< Red color.
    static const Color Green;   ///< Green color.
    static const Color Blue;    ///< Blue color.
    static const Color Yellow;  ///< Yellow color.
    static const Color Cyan;    ///< Cyan color.
    static const Color Magenta; ///< Magenta color.
    static const Color White;   ///< White color.
    static const Color Black;   ///< Black color.
    static const Color Gray;    ///< Gray color.
    static const Color Orange;  ///< Orange color.
    static const Color Purple;  ///< Purple color.
    static const Color Pink;    ///< Pink color.
};