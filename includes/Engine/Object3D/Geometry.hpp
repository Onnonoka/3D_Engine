#include <Object3D/BasicObject.hpp>
#include <Object3D/Face.hpp>
#include <vector>
#include <memory>

/**
 * @brief Represents a geometric structure composed of faces and points.
 */
class Geometry {
public:
    Geometry() = default;

    /**
     * @brief Constructs a Geometry object with specified faces.
     * @param faces The vector of faces defining the geometry.
     */
    Geometry(const std::vector<std::vector<Point>> faces);

    /**
     * @brief Constructs a Geometry object with specified faces.
     * @param faces The vector of faces defining the geometry.
     */
    Geometry(const std::vector<Face> faces);

    /**
     * @brief Creates a new face and adds it to the geometry.
     * @param newFace The vector of points defining the new face.
     */
    void createFace(const std::vector<Point> newFace);

    /**
     * @brief Creates multiple faces and adds them to the geometry.
     * @param newFaces The vector of vectors of points defining the new faces.
     */
    void createFaces(const std::vector<std::vector<Point>> newFaces);

    /**
     * @brief Adds a face to the geometry.
     * @param newFace The face to add.
     */
    void addFace(const Face newFace);

    /**
     * @brief Adds multiple faces to the geometry.
     * @param newFaces The vector of faces to add.
     */
    void addFaces(const std::vector<Face> newFaces);

    /**
     * @brief Retrieves the number of faces in the geometry.
     * @return The number of faces in the geometry.
     */
    size_t getNumberOfFaces() const;

    /**
     * @brief Retrieves the number of points in the geometry.
     * @return The number of points in the geometry.
     */
    size_t getNumberOfPoints() const;

    /**
     * @brief Retrieves the index buffer data representing the geometry's faces.
     * @return The index buffer data.
     */
    std::vector<unsigned int> getIndexBufferData() const;

    /**
     * @brief Retrieves the array buffer data representing the geometry's points.
     * @return The array buffer data.
     */
    std::vector<glm::vec3> getArrayBufferData() const;
    
    /**
     * @brief Retrieves the size of the index buffer data in bytes.
     * @return The size of the index buffer data.
     */
    size_t getIndexBufferDataSize() const;
    
    /**
     * @brief Retrieves the size of the array buffer data in bytes.
     * @return The size of the array buffer data.
     */
    size_t getArrayBufferDataSize() const;

private:

    std::vector<unsigned int> faces;    ///< The list of indices representing the faces of the geometry.

    std::vector<Point> points;          ///< The list of points defining the geometry.
};
