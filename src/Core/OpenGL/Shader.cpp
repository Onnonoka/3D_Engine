#include <Core/OpenGL/Shader.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include <Core/Error/EngineError.hpp>

Shader::Shader() : programID(0) {

}

Shader::~Shader() {
    glDeleteProgram(programID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void Shader::bind() const {
    glUseProgram(programID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void Shader::unbind() const {
    glUseProgram(programID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

void Shader::loadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    // Lecture des fichiers des shaders
    std::string vertexCode = readFile(vertexShaderPath);
    std::string fragmentCode = readFile(fragmentShaderPath);

    // Compilation des shaders
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // Création du programme de shaders
    programID = linkProgram(vertexShader, fragmentShader);

    // Libération des shaders compilés (déjà liés au programme)
    glDeleteShader(vertexShader);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glDeleteShader(fragmentShader);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

unsigned int Shader::compileShader(GLenum type, const std::string& source) {
    unsigned int shaderID = glCreateShader(type);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glCompileShader(shaderID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    // Vérification des erreurs de compilation
    int success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        ENGINE_CRITICAL_ERROR(GET_CTX_ERROR, RenderError::SHADER_BUILD_ERROR, {infoLog});
        return 0;
    }

    return shaderID;
}

unsigned int Shader::linkProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID) {
    unsigned int programID = glCreateProgram();
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glAttachShader(programID, vertexShaderID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glAttachShader(programID, fragmentShaderID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glLinkProgram(programID);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    // Vérification des erreurs de liaison
    int success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(programID, 512, NULL, infoLog);
        ENGINE_CRITICAL_ERROR(GET_CTX_ERROR, RenderError::SHADER_BUILD_ERROR, {infoLog});
        return 0;
    }

    return programID;
}

std::string Shader::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        ENGINE_CRITICAL_ERROR(GET_CTX_ERROR, RenderError::SHADER_FILE_INVALID);
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}