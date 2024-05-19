#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * @brief Handles the creation and management of a GLFW window.
 */
class Window {
public:
    /**
     * @brief Constructor to initialize a GLFW window.
     * @param width The width of the window.
     * @param height The height of the window.
     * @param title The title of the window.
     */
    Window(int width, int height, const char* title);

    /**
     * @brief Destructor responsible for cleaning up the GLFW window.
     */
    ~Window();

    /**
     * @brief Checks if the window should close.
     * @return True if the window should close, false otherwise.
     */
    bool shouldClose() const;

    /**
     * @brief Swaps the front and back buffers and processes window events.
     */
    void swapBuffersAndPollEvents();

    /**
     * @brief Processes input events for the window.
     */
    void processInput();

    /**
     * @brief Sets the current window for OpenGL rendering.
     */
    void setCurrentWindow();

    /**
     * @brief Gets the refresh rate of the window's monitor if available.
     * @return The refresh rate of the window's monitor if available, otherwise returns a default value.
     */
    int getRefreshRate() const;

private:
    GLFWwindow* window;     ///< Pointer to the GLFW window.
    int width, height;      ///< Width and height of the window.
    const char* title;      ///< Title of the window.

    /**
     * @brief Callback function for framebuffer size changes.
     * @param window The GLFW window.
     * @param width The new width of the framebuffer.
     * @param height The new height of the framebuffer.
     */
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    /**
     * @brief Initializes the OpenGL context.
     */
    static void glInit();

    /**
     * @brief Gets the OpenGL context.
     */
    static void getGlContext();
};