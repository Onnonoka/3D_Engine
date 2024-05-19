#include <Object3D/Group.hpp>
#include <iostream>
#include <algorithm>

void Group::add(Renderable *object) {
    childrens.push_back(object);
}

void Group::remove(const Renderable *object) {
    std::vector<Renderable *>::iterator it = std::find(childrens.begin(), childrens.end(), object);
    if (it != childrens.end()) {
        childrens.erase(it);
    }
}

void Group::clear() {
    childrens.clear();
}

std::vector<Renderable*> Group::getChildrens() {
    return childrens;
}

Renderable& Group::getObject(unsigned int index) {
    return *(childrens[index]);
}

size_t Group::getNumberOfChildren() const {
    return childrens.size();
}

void Group::render(const glm::mat4 parentModelMatrix, const Renderer& renderer) {
    
    glm::mat4 global_transform = parentModelMatrix * getTransformationMatrix();
    for (Renderable* child : getChildrens()) {
        child->render(global_transform, renderer);
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