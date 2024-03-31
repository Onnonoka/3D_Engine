#pragma once

#include <Object3D/BasicObject.hpp>
#include <glm/glm.hpp>

/**
 * @brief Represents a point in 3D space.
 */
class Point : public BasicObject {
public:
    /**
     * @brief Default constructor for Point.
     * Initializes the point at the origin (0, 0, 0).
     */
    Point() = default;

    /**
     * @brief Constructs a Point with specified coordinates.
     * @param x The x-coordinate of the point.
     * @param y The y-coordinate of the point.
     * @param z The z-coordinate of the point.
     */
    Point(float x, float y, float z);

    /**
     * @brief Constructs a Point from a position vector.
     * @param position The position vector representing the coordinates of the point.
     */
    Point(glm::vec3 position);

    /**
     * @brief Equality operator for comparing two points.
     * @param other The other point to compare with.
     * @return True if the two points are equal, false otherwise.
     */
    bool operator==(const Point& other) const;

    /**
     * @brief Inequality operator for comparing two points.
     * @param other The other point to compare with.
     * @return True if the two points are not equal, false otherwise.
     */
    bool operator!=(const Point& other) const;

};

namespace std {
    template <>
    struct hash<Point> {
        std::size_t operator()(const Point& p) const {
            // Combine the hash values of x, y, and z using XOR (^) to reduce collisions
            std::size_t hashValue = 0;
            hash<float> floatHasher;
            hashValue ^= floatHasher(p.getPosition().x) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            hashValue ^= floatHasher(p.getPosition().y) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            hashValue ^= floatHasher(p.getPosition().z) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            return hashValue;
        }
    };
}
