#pragma once

#include <Core/Color.hpp>
#include <Object3D/Geometry.hpp>
#include <Object3D/Point.hpp>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>


/**
 * @class Material
 * @brief Class representing a material for managing colors associated with a geometric object.
 * 
 * The Material class provides functionality to manage colors associated with geometric objects.
 * It allows setting and retrieving colors for individual points, as well as updating material buffer data.
 */
class Material : public Dirty {
public:
    /**
     * @brief Enum representing the fields that can be marked as dirty in the material.
     */
    enum DirtyField {
        COLOR ///< Indicates the color field
    };

    /**
     * @brief Constructs a Material object with an optional default color.
     * 
     * @param defaultColor The default color to use for points.
     */
    Material(const Color defaultColor = Color::Gray);

    /**
     * @brief Sets the default color for points.
     * 
     * @param color The default color to set.
     */
    void setDefaultColor(Color color);

    /**
     * @brief Sets the color for a specific point.
     * 
     * @param point The point for which to set the color.
     * @param color The color to set for the point.
     */
    void setPointColor(Point point, Color color);

    /**
     * @brief Retrieves the color associated with a specific point.
     * 
     * @param point The point for which to retrieve the color.
     * @return The color associated with the point.
     */
    Color getPointColor(Point point);

    /**
     * @brief Updates the material buffer data based on the provided points.
     * 
     * @param points The points used to update the material buffer data.
     */
    void updateMaterialBufferData(const std::vector<glm::vec3> points);

    /**
     * @brief Retrieves the material buffer data containing colors.
     * 
     * @return A vector containing color data for the material buffer.
     */
    std::vector<Color> getMaterialBufferData();

    /**
     * @brief Retrieves the size of the material buffer data.
     * 
     * @return The size of the material buffer data.
     */
    size_t getMaterialBufferDataSize();

    /**
     * @brief Surcharge de l'opérateur == pour comparer deux matériaux.
     * @param other L'autre matériau à comparer.
     * @return true si les deux matériaux sont égaux, false sinon.
     */
    bool operator==(const Material& other) const;

private:
    Color defaultColor; ///< The default color for points.

    std::vector<Color> materialBufferData; ///< Vector containing color data for the material buffer.
    std::unordered_map<Point, Color> colorMap; ///< Map storing colors for individual points.
};