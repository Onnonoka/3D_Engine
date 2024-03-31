#include <Basic/Dirty.hpp>

Dirty::Dirty(const unsigned long size) {
    // TODO Ajouter une erreur si size > long
    dirtyFlags = 0L;
}

bool Dirty::isDirty() const {
    return dirtyFlags != 0;
}

bool Dirty::isDirty(const unsigned int index) const {
    return (dirtyFlags & (1 << index)) == (1 << index);
}

void Dirty::makeDirty() {
    dirtyFlags |= 0xffffffff;
}

void Dirty::makeDirty(const unsigned int index) {
    dirtyFlags = dirtyFlags | (1 << index);
}

void Dirty::clean() {
    dirtyFlags = 0;
}

void Dirty::clean(const unsigned int index) {
    dirtyFlags = dirtyFlags & (0 << index);
}