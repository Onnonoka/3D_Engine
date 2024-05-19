#pragma once


#include <glad/glad.h>

class UniformBuffer {
public:
    UniformBuffer();
    ~UniformBuffer();

    void bind() const;
    void unbind() const;
    void setData(unsigned int size, const void* data, GLenum usage) const;

private:
    unsigned int uniformBuferID;
};