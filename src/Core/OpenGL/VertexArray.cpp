#include <Core/OpenGL/VertexArray.hpp>
#include <Core/Error/EngineError.hpp>
#include <cstdint>

VertexArray::VertexArray() {
    glCreateVertexArrays(1, &vertexArray);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &vertexArray);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void VertexArray::bind() const {
    glBindVertexArray(vertexArray);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void VertexArray::addBuffer(const VertexBuffer& vb, unsigned int index, 
                            int size, GLenum type, GLboolean normalized, 
                            GLsizei stride, const void* pointer) {

    glVertexArrayVertexBuffer(vertexArray, index, vb.getID(), 
                              pointer ? static_cast<GLintptr>(reinterpret_cast<std::intptr_t>(pointer)) : 0, stride);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glVertexArrayAttribFormat(vertexArray, index, size, type, normalized, 0);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glEnableVertexArrayAttrib(vertexArray, index);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glVertexArrayAttribBinding(vertexArray, index, index);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void VertexArray::addBuffer(const ElementBuffer& eb) {
    glVertexArrayElementBuffer(vertexArray, eb.getID());
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}