#pragma once

#include <iostream>
#include <glad/glad.h>

class VertexBuffer {
public:

    VertexBuffer();

    VertexBuffer(size_t size, void *data);

    ~VertexBuffer();

    void setData(size_t size, void *data);

    unsigned int getID() const;

private:
    GLuint vertexBufferID;
};