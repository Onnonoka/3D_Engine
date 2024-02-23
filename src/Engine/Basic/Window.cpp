#include "Basic/Window.hpp"
#include <iostream>
#include <Error/EngineError.hpp>
#include <glad/glad.h>

Window::Window(int width, int height, const char* title) : width(width), height(height), title(title) {
    char test;
    Window::glInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        std::cin >> test;
        std::exit(EXIT_FAILURE);
    }
    setCurrentWindow();
	glfwSwapInterval(true);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    getGlContext();
}

Window::~Window() {
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffersAndPollEvents() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::setCurrentWindow() {
    glfwMakeContextCurrent(window);
}

void Window::glInit() {
    if (!glfwInit()) {
        ENGINE_CRITICAL_ERROR(GET_CTX_ERROR, EngineError::INITIALIZATION_ERROR, {"glfw init error."});
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifndef NDEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    #endif
}

void Window::getGlContext() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ENGINE_CRITICAL_ERROR(GET_CTX_ERROR, EngineError::INITIALIZATION_ERROR, {"glad init error."});
    }

}

int Window::getRefreshRate() const {
    int windowRefreshRate = 1;
    if (window) {
        GLFWmonitor* monitor = glfwGetWindowMonitor(window);
        if (!monitor) {
            monitor = glfwGetPrimaryMonitor();
        }
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        windowRefreshRate = mode->refreshRate;
    }
    return windowRefreshRate;
}