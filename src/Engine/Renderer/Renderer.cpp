#include "Renderer/Renderer.hpp"
#include <iostream> // For logs
#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include <Error/EngineError.hpp>

void Renderer::loadShaders(const std::string& vertexShaderFile, const std::string& fragmentShaderFile) {
    std::ifstream vertexShaderStream(vertexShaderFile);
    std::ifstream fragmentShaderStream(fragmentShaderFile);
    std::stringstream vertexShaderCode; 
    std::stringstream fragmentShaderCode;
    std::string vertexShaderCodeString; 
    std::string fragmentShaderCodeString;
    const GLchar *fragmentShaderSource;
    const GLchar *vertexShaderSource;
    int success;

    // Opening and reading shader source code
    if (vertexShaderStream.is_open() && fragmentShaderStream.is_open()) {
        vertexShaderCode << vertexShaderStream.rdbuf();
        fragmentShaderCode << fragmentShaderStream.rdbuf();

        vertexShaderStream.close();
        fragmentShaderStream.close();

        vertexShaderCodeString = vertexShaderCode.str();
        vertexShaderSource = vertexShaderCodeString.c_str();
        fragmentShaderCodeString = fragmentShaderCode.str();
        fragmentShaderSource = fragmentShaderCodeString.c_str();
    } else {
        ENGINE_CRITICAL_ERROR(GET_CTX_ERROR, RenderError::SHADER_FILE_INVALID);
    }

    // building the shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glCompileShader(vertexShader);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    // Checking for compilation errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        ENGINE_CRITICAL_ERROR(GET_CTX_ERROR, RenderError::SHADER_BUILD_ERROR, {vertexShaderCodeString, infoLog});
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glCompileShader(fragmentShader);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);

    // Checking for compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        ENGINE_CRITICAL_ERROR(GET_CTX_ERROR, RenderError::SHADER_BUILD_ERROR, {fragmentShaderCodeString, infoLog});
    }

    // Creating the shader program and attaching the shaders
    shaderProgram = glCreateProgram();
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glAttachShader(shaderProgram, vertexShader);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glAttachShader(shaderProgram, fragmentShader);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glLinkProgram(shaderProgram);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    
    glDeleteShader(vertexShader);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
    glDeleteShader(fragmentShader);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}

Renderer::~Renderer() {
    glDeleteProgram(shaderProgram);
    CHECK_ENGINE_GL_ERROR(GET_CTX_ERROR);
}
