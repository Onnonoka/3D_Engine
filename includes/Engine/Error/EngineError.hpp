#pragma once

#include <iostream>
#include <vector>
#include <string>

#define GET_CTX_ERROR std::string(__FILE__) + ":" + std::to_string(__LINE__)

enum class ErrorCodes : unsigned int {
    NO_ERROR = 0,
    UNKNOW_ERROR = 1,
    ENGINE_ERROR_START = 2,
    RENDER_ERROR_START = 5,
};

enum class EngineError : unsigned int {
    INITIALIZATION_ERROR = static_cast<unsigned int>(ErrorCodes::ENGINE_ERROR_START),
    WINDOW_CREATE_ERROR,
};

enum class RenderError : unsigned int {
    SHADER_FILE_INVALID = static_cast<unsigned int>(ErrorCodes::RENDER_ERROR_START),
    SHADER_BUILD_ERROR,
    RENDERER_NOT_INITIALIZED,
};

/**
 * @brief Displays an error with context, error code, and optional comments.
 * @param ctx The context of the error.
 * @param error The error code.
 * @param comments Additional comments to detail the error (optional).
 */
void displayError(std::string ctx, unsigned int error, std::vector<std::string> comments);

/**
 * @brief Stops program execution critically.
 */
void criticalStop();

/**
 * @brief Generates a critical error with program termination.
 * @tparam T Type of error (enum).
 * @param ctx The context of the error.
 * @param error The error code.
 * @param comments Additional comments to detail the error (optional).
 */
template<typename T>
void ENGINE_CRITICAL_ERROR(std::string ctx, T error, std::vector<std::string> comments = {}) {
    displayError(ctx, static_cast<unsigned int>(error), comments);
    criticalStop();
}

/**
 * @brief Indicates an implementation error without program termination.
 * @tparam T Type of error (enum).
 * @param ctx The context of the error.
 * @param error The error code.
 * @param comments Additional comments to detail the error (optional).
 */
template<typename T>
void ENGINE_SKIP_IMPLEMENTATION_ERROR(std::string ctx, T error, std::vector<std::string> comments = {}) {
    displayError(ctx, static_cast<unsigned int>(error), comments);
}

/**
 * @brief Checks engine-specific OpenGL errors.
 * @param ctx The context for OpenGL error checking.
 * @param comments Additional comments to detail the error (optional).
 */
void CHECK_ENGINE_GL_ERROR(std::string ctx, std::vector<std::string> comments = {});