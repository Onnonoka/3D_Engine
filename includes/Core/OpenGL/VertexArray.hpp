#pragma once

#include <Core/OpenGL/VertexBuffer.hpp>
#include <Core/OpenGL/ElementBuffer.hpp>
#include <glad/glad.h>

class VertexArray {
public:

    VertexArray();

    ~VertexArray();

    void bind() const;

    void unbind() const;

    void addBuffer(const VertexBuffer& vb, unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
    
    void addBuffer(const ElementBuffer& eb);

private:
    GLuint vertexArray = 0;
};