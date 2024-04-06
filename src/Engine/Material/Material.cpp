#include <Material/Material.hpp>
#include <Core/Error/EngineError.hpp>

Material::Material(Color newDefaultColor) {
    defaultColor = newDefaultColor;
}

void Material::setDefaultColor(Color color) {
    defaultColor = color;
    makeDirty(COLOR);
}

void Material::setPointColor(Point point, Color color) {
    colorMap.insert({point, color});
    makeDirty(COLOR);
}

Color Material::getPointColor(Point point) {
    auto it = colorMap.find(point);

    if (it != colorMap.end()) {
        return it->second;
    }

    return defaultColor;
}

void Material::updateMaterialBufferData(const std::vector<glm::vec3> points) {
    materialBufferData.clear();
    for (Point point : points) {
        materialBufferData.push_back(getPointColor(point));
    }
}

std::vector<Color> Material::getMaterialBufferData() {
    return materialBufferData;
}

size_t Material::getMaterialBufferDataSize() {
    return materialBufferData.size() * sizeof(Color);
}

bool Material::operator==(const Material& other) const {
    // Comparez les membres du matériau un par un
    return (
        getDirtyFlags() == other.getDirtyFlags() &&
        defaultColor == other.defaultColor &&
        materialBufferData == other.materialBufferData &&
        colorMap == other.colorMap
    );
}
