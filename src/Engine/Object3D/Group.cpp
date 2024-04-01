#include <Object3D/Group.hpp>
#include <iostream>
#include <algorithm>

void Group::add(Object3D *object) {
    childrens.push_back(object);
}

void Group::remove(const Object3D *object) {
    std::vector<Object3D *>::iterator it = std::find(childrens.begin(), childrens.end(), object);
    if (it != childrens.end()) {
        childrens.erase(it);
    }
}

void Group::clear() {
    childrens.clear();
}

std::vector<Object3D*> Group::getChildrens() {
    return childrens;
}

Object3D& Group::getObject(unsigned int index) {
    return *(childrens[index]);
}

size_t Group::getNumberOfChildren() const {
    return childrens.size();
}

void Group::render(const Camera& camera, const glm::mat4 parentModelMatrix, const GLuint shaderProgram) {
    
    glm::mat4 global_transform = parentModelMatrix * getTransformationMatrix();
    for (Object3D* child : getChildrens()) {
        child->render(camera, global_transform, shaderProgram);
    }
}

bool Group::operator==(const Group& other) const {
    if (other.getNumberOfChildren() != getNumberOfChildren()) {
        return false;
    }
    
    for (unsigned int i = 0; i < other.getNumberOfChildren(); ++i) {
        if (!(childrens.at(i) == other.childrens.at(i))) {
            return false;
        }
    }
    
    return true;
}