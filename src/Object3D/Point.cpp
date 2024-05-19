#include <Object3D/Point.hpp>
#include <iostream>

Point::Point(float x, float y, float z)
    : Point(glm::vec3(x, y, z)) { }

Point::Point(glm::vec3 position)
    : BasicObject(position, glm::vec3(0.0f), glm::vec3(1.0f)) { }

bool Point::operator==(const Point& other) const {
    glm::vec3 pos = getPosition();
    glm::vec3 otherPos = other.getPosition();
    return pos.x == otherPos.x && pos.y == otherPos.y && pos.z == otherPos.z;
}

bool Point::operator!=(const Point& other) const {
    glm::vec3 pos = getPosition();
    glm::vec3 otherPos = other.getPosition();
    return pos.x != otherPos.x && pos.y != otherPos.y && pos.z != otherPos.z;
}
