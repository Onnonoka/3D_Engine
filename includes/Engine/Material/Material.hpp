#pragma once

#include <Basic/Color.hpp>
#include <Object3D/Geometry.hpp>
#include <Object3D/Point.hpp>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>


/**
 * @class Material
 * @brief Class representing a material for managing colors associated with a geometric object.
 */
class Material : public Dirty {
public:
    enum DirtyField {
        COLOR
    };

    Material(const Color defaultColor = Color::Gray);

    void setDefaultColor(Color color);

    void setPointColor(Point point, Color color);

    Color getPointColor(Point point);

    void Material::updateMaterialbufferData(const std::vector<glm::vec3> points);

    std::vector<Color> getMaterialBufferData();

    size_t getMaterialBufferDataSize();

private:
    Color defaultColor;

    std::vector<Color> materialBufferData;
    std::unordered_map<Point, Color> colorMap;
};