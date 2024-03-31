#include <Object3D/Geometry.hpp>
#include <algorithm>
#include <iostream>
#include <Error/EngineError.hpp>

Geometry::Geometry(const std::vector<std::vector<Point>> faces)
    : Dirty(2) {
    createFaces(faces);
}

Geometry::Geometry(const std::vector<Face> faces) {
    addFaces(faces);
}

void Geometry::createFace(const std::vector<Point> newFace) {
    if (newFace.size() > 3) {
        // TODO A tesselation is needed
    }

    // For all points in the face
    for (Point point : newFace) {
        // We check if the point already exist
        std::vector<Point>::iterator it = std::find(points.begin(), points.end(), point);
        int index = static_cast<int>(std::distance(points.begin(), it));
        if (it == points.end()) {
            // If it not exist we create it at the end of the points vector
            points.push_back(point);
            // We set the Verticies Dirty Flag to true for Object3D reconstructions.
            makeDirty(VERTICES);
        }

        // Push the point face index into faces vector
        // if std::find don't find the element it ref after the __last element
        // index should be equal to points.size()
        faces.push_back(static_cast<unsigned int>(index));
        // We set the INDICES Dirty Flag to true for Object3D reconstructions.
        makeDirty(INDICES);
    }
}

void Geometry::createFaces(const std::vector<std::vector<Point>> newFaces) {
    for (std::vector<Point> newFace : newFaces) {
        createFace(newFace);
    }
}

void Geometry::addFace(const Face face) {
    createFace(face.getPoints());
}

void Geometry::addFaces(const std::vector<Face> newFaces) {
    for (Face face : newFaces) {
        createFace(face.getPoints());
    }
}

size_t Geometry::getNumberOfFaces() const {
    return faces.size();
}

size_t Geometry::getNumberOfPoints() const {
    return points.size();
}

std::vector<unsigned int> Geometry::getIndexBufferData() const {
    return faces;
}

std::vector<glm::vec3> Geometry::getArrayBufferData() const {
    std::vector<glm::vec3> computedPoints;
    for (Point point : points) {
        computedPoints.push_back(point.getPosition());
    }
    return computedPoints;
}

size_t Geometry::getIndexBufferDataSize() const {
    return faces.size() * sizeof(unsigned int);
}

size_t Geometry::getArrayBufferDataSize() const {
    return points.size() * sizeof(glm::vec3);
}
