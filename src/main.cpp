#include <Basic/Window.hpp>
#include <Renderer/MinimalRrenderer.hpp>
#include <Object3D/SimpleObject/Cube.hpp>
#include <Error/EngineError.hpp>
#include <Basic/FPSCounter.hpp>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/constants.hpp>

int main(int argc, char *argv[]) {
    Window window(1920, 1080, "OpenGL Window");  
    MinimalRenderer renderer = MinimalRenderer();

    // Initialisation de FPSCounter avec le taux de rafraîchissement de l'écran
    FPSCounter counter = FPSCounter();
    counter.setInitialFPS(window.getRefreshRate());

    Cube cube = Cube();

    Camera camera = Camera();
    camera.setScreenSize(1920, 1080);
    camera.setPosition(glm::vec3(-2, 0, 0));
    counter.start();
    while (!window.shouldClose()) {
        window.processInput();

        counter.calculateFPS();
        float delta = 1.0f / counter.getFPS();
        // Code de rendu OpenGL
        glm::vec3 rotateValue = cube.getRotation();
        rotateValue.y += (360.0f / 10.0f) * delta;
        rotateValue.x += (360.0f / 10.0f) * delta;
        cube.setRotation(rotateValue);

        renderer.render(camera, cube);

        window.swapBuffersAndPollEvents();
    }

    return 0;
}