
#include <Core/OpenGL/VertexBuffer.hpp>
#include <Core/Error/EngineError.hpp>

VertexBuffer::VertexBuffer() {
    glCreateBuffers(1, &vertexBufferID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

VertexBuffer::VertexBuffer(size_t size, void *data) {
    glCreateBuffers(1, &vertexBufferID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    setData(size, data);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &vertexBufferID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void VertexBuffer::setData(size_t size, void *data) {
    glNamedBufferData(vertexBufferID, size, data, GL_STATIC_DRAW);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

unsigned int VertexBuffer::getID() const {
    return vertexBufferID;
}