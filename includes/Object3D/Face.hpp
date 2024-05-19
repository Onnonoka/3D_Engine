#pragma once

#include <Object3D/BasicObject.hpp>
#include <Object3D/Point.hpp>
#include <vector>
#include <memory>

/**
 * @brief Represents a face in a geometric structure.
 */
class Face {
public:

    Face() = default;

    /**
     * @brief Constructs a Face object with specified points.
     * @param newPoints The vector of points defining the face.
     */
    Face(std::vector<Point> newPoints);
    
    /**
     * @brief Constructs a Face object with specified points.
     * @param newPoints The vector of points defining the face.
     */
    Face(std::vector<glm::vec3> newPoints);
    
    /**
     * @brief Retrieves all points defining the face.
     * @return A vector of points.
     */
    std::vector<Point> getPoints() const;

    /**
     * @brief Retrieves a specific point from the face by index.
     * @param index The index of the point.
     * @return The point at the specified index.
     */
    Point getPoint(unsigned int index) const;

    /**
     * @brief Adds a point to the face.
     * @param point The point to add.
     */
    void addPoint(Point point);

    /**
     * @brief Adds multiple points to the face.
     * @param newPoints The vector of points to add.
     */
    void addPoints(std::vector<Point> newPoints);

    /**
     * @brief Sets a point at a specific index.
     * @param index The index where the point will be set.
     * @param point The new point to set.
     */
    void setPoint(unsigned int index, Point point);

    /**
     * @brief Removes a point from the face by index.
     * @param index The index of the point to remove.
     */
    void removePoint(unsigned int index);

    /**
     * @brief Gets the number of points in the face.
     * @return The number of points in the face.
     */
    size_t numberOfPoints() const;

private:

    std::vector<Point> points;  ///< The list of points defining the face.
};