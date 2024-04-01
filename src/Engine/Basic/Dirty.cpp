#include <Basic/Dirty.hpp>
#include <Error/EngineError.hpp>
#include <limits>

Dirty::Dirty() {
    dirtyFlags = 0L;
}

bool Dirty::isDirty() const {
    return dirtyFlags != 0;
}

bool Dirty::isDirty(const unsigned int index) const {
    if (index > std::numeric_limits<DirtyField>::digits) {
        ENGINE_CRITICAL_ERROR(GET_CTX_ERROR, EngineError::DIRTY_OUT_OF_RANGE);
    }
    return (dirtyFlags & (1 << index)) == (1 << index);
}

void Dirty::makeDirty() {
    dirtyFlags |= 0xffffffff;
}

void Dirty::makeDirty(const unsigned int index) {
    if (index > std::numeric_limits<DirtyField>::digits) {
        ENGINE_CRITICAL_ERROR(GET_CTX_ERROR, EngineError::DIRTY_OUT_OF_RANGE);
    }
    dirtyFlags = dirtyFlags | (1 << index);
}

void Dirty::cleanDirtyFlags() {
    dirtyFlags = 0;
}

void Dirty::cleanDirtyFlag(const unsigned int index) {
    if (index > std::numeric_limits<long>::digits) {
        ENGINE_CRITICAL_ERROR(GET_CTX_ERROR, EngineError::DIRTY_OUT_OF_RANGE);
    }
    dirtyFlags = dirtyFlags & (0 << index);
}

DirtyField Dirty::getDirtyFlags() const {
    return dirtyFlags;
}