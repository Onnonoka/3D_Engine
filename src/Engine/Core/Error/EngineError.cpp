#include <Core/Error/EngineError.hpp>
#include <map>
#include <glad/glad.h>

static std::map<unsigned int, std::string> errorMessages = {
    {static_cast<unsigned int>(ErrorCodes::NO_ERROR), "No error."},
    {static_cast<unsigned int>(ErrorCodes::UNKNOW_ERROR), "Unknow error."},
    {static_cast<unsigned int>(EngineError::INITIALIZATION_ERROR), "Failled to initilize engine."},
    {static_cast<unsigned int>(EngineError::WINDOW_CREATE_ERROR), "Failled to create a window."},
    {static_cast<unsigned int>(RenderError::SHADER_FILE_INVALID), "Invalid shader file path."},
    {static_cast<unsigned int>(RenderError::SHADER_BUILD_ERROR), "Shader file cannot be build."},
    {static_cast<unsigned int>(RenderError::RENDERER_NOT_INITIALIZED), "A renderer cannot render a scene without shaders or shader program."},
};

std::string GLCheckError(GLenum errorCode) {
    switch (errorCode) {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.";
        default:
            return "No error found.";
    }
}

void criticalStop() {
    std::cout << "Press Enter to exit...";
    std::cin.get();
    std::exit(EXIT_FAILURE);
}

std::string getErrorMessage(unsigned int code) {
    auto it = errorMessages.find(code);
    if (it != errorMessages.end()) {
        return it->second;
    } else {
        return "Unknown error.";
    }
}

void displayError(std::string ctx, unsigned int error, std::vector<std::string> comments) {
    std::cerr << "------------------------------------------------------------------------" << std::endl;
    std::cerr << "Called from: " << ctx << std::endl;
    
    std::cerr << getErrorMessage(error) << std::endl;

    if (!comments.empty()) {
        std::cerr << "Comments :" << std::endl;
        for (const auto& comment : comments) {
            std::cerr << "- " << comment << std::endl;
        }
    }

    std::cerr << "------------------------------------------------------------------------" << std::endl;
}

void CHECK_ENGINE_GL_ERROR(std::string ctx, std::vector<std::string> comments) {
    #ifndef NDEBUG
        GLenum error;
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::string errorMessage = GLCheckError(error);
            std::vector<std::string> combinedComments = { "OpenGL Error: " + errorMessage };
            combinedComments.insert(combinedComments.end(), comments.begin(), comments.end());
            ENGINE_CRITICAL_ERROR(ctx, error, combinedComments);
        }
    #endif
}
