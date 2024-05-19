#pragma once

#include <glad/glad.h>

class ElementBuffer {
public:

    ElementBuffer();
    ElementBuffer(const unsigned int* data, size_t size);
    ~ElementBuffer();

    void bind() const;
    void unbind() const;

    void setData(const unsigned int* data, size_t size);

    unsigned int getID() const;

private:
    unsigned int elementBufferID;
};