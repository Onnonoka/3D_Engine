#include <Core/OpenGL/UniformBuffer.hpp>
#include <Core/Error/EngineError.hpp>

UniformBuffer::UniformBuffer() {
    glGenBuffers(1, &uniformBuferID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

UniformBuffer::~UniformBuffer() {
    glDeleteBuffers(1, &uniformBuferID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void UniformBuffer::bind() const {
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuferID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void UniformBuffer::unbind() const {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void UniformBuffer::setData(unsigned int size, const void* data, GLenum usage) const {
    glNamedBufferData(uniformBuferID, size, data, usage);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuferID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}
