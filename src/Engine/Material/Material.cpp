#include <Material/Material.hpp>
#include <Error/EngineError.hpp>

Material::Material(const std::vector<glm::vec3> vertices, const std::vector<unsigned int> faces, const Color defaultColor) {
    vertexForFacesColor.resize(vertices.size());
    facesOrder = faces;
    for (int i = 0; i < faces.size() / 3; i++) {
        int offset = i * 3;
        vertexForFacesColor[faces[offset]][i] = defaultColor;
        vertexForFacesColor[faces[offset + 1]][i] = defaultColor;
        vertexForFacesColor[faces[offset + 2]][i] = defaultColor;
    }
}

Material::~Material() {
    glDeleteBuffers(1, &vbo);
}

void Material::setColor(const Color color) {
    for (auto& vertexElem : vertexForFacesColor) {
        for (auto& vertexColor : vertexElem) {
            vertexColor.second = color;
        }
    }
}

void Material::setVertexColor(const int index, const Color color) {
    for (auto& vertexElem : vertexForFacesColor[index]) {
            vertexElem.second = color;
    }
}

void Material::setFaceColor(const int index, const Color color) {
    for (auto& vertexElem : vertexForFacesColor) {
        for (auto& vertexColor : vertexElem) {
            if (index == vertexColor.first) {
                vertexColor.second = color;
                break;
            }
        }
    }
}

void Material::setVertexForFaceColor(const int vertexIndex, const unsigned int faceIndex, const Color color) {
    vertexForFacesColor[vertexIndex][faceIndex] = color;
}

Color Material::getVertexForFaceColor(const int vertexIndex, const unsigned int faceIndex) const {
    return vertexForFacesColor.at(vertexIndex).at(faceIndex);
}

GLuint Material::getVBO() const {
    return vbo;
}