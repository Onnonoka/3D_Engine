#include <Object3D/Sample/Cube.hpp>
#include <Core/Color.hpp>
#include <Core/Error/EngineError.hpp>
#include <iostream>
#include <memory>

Cube::Cube(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) 
    : Object3D(position, rotation, scale) {

    // Create Cube Points
    Point p0 = Point(-0.5f, -0.5f, -0.5f);
    Point p1 = Point(0.5f, -0.5f, -0.5f);
    Point p2 = Point(0.5f, 0.5f, -0.5f);
    Point p3 = Point(-0.5f, 0.5f, -0.5f);
    Point p4 = Point(-0.5f, -0.5f, 0.5f);
    Point p5 = Point(0.5f, -0.5f, 0.5f);
    Point p6 = Point(0.5f, 0.5f, 0.5f);
    Point p7 = Point(-0.5f, 0.5f, 0.5f);

    // Create Cube Faces
    // Front
    Face front1 = Face({p2, p3, p0});
    Face front2 = Face({p1, p2, p0});
    // Right
    Face right1 = Face({p1, p6, p2});
    Face right2 = Face({p5, p6, p1});
    // Back
    Face back1 = Face({p7, p6, p5});
    Face back2 = Face({p4, p7, p5});
    // Left
    Face left1 = Face({p3, p7, p4});
    Face left2 = Face({p0, p3, p4});
    // Top
    Face top1 = Face({p2, p7, p3});
    Face top2 = Face({p2, p6, p7});
    // Bottom
    Face bottom1 = Face({p4, p5, p0});
    Face bottom2 = Face({p5, p1, p0});

    // Adding faces to geometry
    Geometry geo = Geometry({
        front1, front2,
        right1, right2,
        back1, back2,
        left1, left2,
        top1, top2,
        bottom1, bottom2
    });

    // Bind the geometry to this object
    setGeometry(geo);

}