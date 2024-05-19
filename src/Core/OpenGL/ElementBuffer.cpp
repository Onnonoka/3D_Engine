#include <Core/OpenGL/ElementBuffer.hpp>
#include <Core/Error/EngineError.hpp>

ElementBuffer::ElementBuffer() {
    glCreateBuffers(1, &elementBufferID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

ElementBuffer::ElementBuffer(const unsigned int* data, size_t size) {
    glCreateBuffers(1, &elementBufferID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    setData(data, size);
}

ElementBuffer::~ElementBuffer() {
    glDeleteBuffers(1, &elementBufferID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void ElementBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void ElementBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void ElementBuffer::setData(const unsigned int* data, size_t size) {
    glNamedBufferData(elementBufferID, size, data, GL_STATIC_DRAW);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

unsigned int ElementBuffer::getID() const {
    return elementBufferID;
}