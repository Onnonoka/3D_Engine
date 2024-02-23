#pragma once

#include <Basic/Color.hpp>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

/**
 * @class Material
 * @brief Class representing a material for managing colors associated with a geometric object.
 */
class Material {
public:
    /**
     * @brief Constructor for a material independent of a geometric object.
     * @param vertices Vectors of vertex positions.
     * @param faces Indices of faces defining vertex relations.
     * @param defaultColor Default color of the material.
     */
    Material(const std::vector<glm::vec3> vertices, const std::vector<unsigned int> faces, const Color defaultColor = Color::Black);

    /**
     * @brief Copy constructor to create a new instance of Material from an existing instance.
     * @param mat Existing instance of Material to copy.
     */
    Material(const Material &mat);

    /**
     * @brief Destructor for Material.
     */
    ~Material();

    /**
     * @brief Sets the color for the entire material.
     * @param color Color to set for the entire material.
     */
    void setColor(const Color color);

    /**
     * @brief Sets the color for a specific vertex.
     * @param index Index of the vertex.
     * @param color Color to set for the vertex.
     */
    void setVertexColor(const int index, const Color color);

    /**
     * @brief Sets the color for a specific face.
     * @param index Index of the face.
     * @param color Color to set for the face.
     */
    void setFaceColor(const int index, const Color color);

    /**
     * @brief Sets the color for a specific vertex within a specific face.
     * @param vertexIndex Index of the vertex.
     * @param faceIndex Index of the face.
     * @param color Color to set for the vertex within the face.
     */
    void setVertexForFaceColor(const int vertexIndex, const unsigned int faceIndex, const Color color);

    /**
     * @brief Retrieves the color of a specific vertex.
     * @param index Index of the vertex.
     * @return Color of the specified vertex.
     */
    Color getVertexForFaceColor(const int vertexIndex, const unsigned int faceIndex) const;


    /**
     * @brief Retrieves the OpenGL buffer associated with the material.
     * @return Identifier of the OpenGL buffer.
     */
    GLuint getVBO() const;

private:
    std::vector<std::unordered_map<unsigned int, Color>> vertexForFacesColor;    ///< Map storing colors for each vertex within each face.

    std::vector<unsigned int> facesOrder;

    GLuint vbo = 0;                                                             ///< Identifier for the OpenGL buffer associated with the material.
};