#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
public:
    Shader();
    ~Shader();

    void loadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void bind() const;
    void unbind() const;

private:
    unsigned int programID;

    unsigned int compileShader(GLenum type, const std::string& source);
    unsigned int linkProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID);
    std::string readFile(const std::string& filePath);
};
