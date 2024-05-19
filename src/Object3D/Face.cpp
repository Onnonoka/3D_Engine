#include <Object3D/Face.hpp>
#include <Core/Error/EngineError.hpp>
#include <algorithm>

Face::Face(const std::vector<Point> newPoints) {
    addPoints(newPoints);
}

Face::Face(const std::vector<glm::vec3> newPoints) {
    for (glm::vec3 point : newPoints) {
        addPoint(Point(point));
    }
}

std::vector<Point> Face::getPoints() const {
    return points;
}

Point Face::getPoint(unsigned int index) const {
    return points[index];
}

void Face::addPoint(const Point point) {
    std::vector<Point>::iterator it = std::find(points.begin(), points.end(), point);
    if (it == points.end()) {
        points.push_back(point);
    }
}

void Face::addPoints(const std::vector<Point> newPoints) {
    for (Point point : newPoints) {
        addPoint(point);
    }
}

void Face::setPoint(unsigned int index, Point point) {
    points[index] = point;
}

void Face::removePoint(unsigned int index) {
    points.erase(points.begin() + index);
}

size_t Face::numberOfPoints() const {
    return points.size();
}