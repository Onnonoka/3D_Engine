#include <Core/Window.hpp>
#include <Renderer/MinimalRrenderer.hpp>
#include <Object3D/Sample/Cube.hpp>
#include <Object3D/Group.hpp>
#include <Core/Error/EngineError.hpp>
#include <Core/FPSCounter.hpp>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/constants.hpp>

int main() {
    Window window(1920, 1080, "OpenGL Window");  
    MinimalRenderer renderer = MinimalRenderer();

    // Initialisation de FPSCounter avec le taux de rafraîchissement de l'écran
    FPSCounter counter = FPSCounter();
    counter.setInitialFPS(window.getRefreshRate());

    Group grp1 = Group();
    Cube cube1 = Cube();
    Cube cube2 = Cube();

    cube1.translate(glm::vec3(0, -1, 0));
    cube2.translate(glm::vec3(0, 1, 0));
    cube1.scaleBy(glm::vec3(0.5, 0.5, 0.5));
    cube2.scaleBy(glm::vec3(0.5, 0.5, 0.5));
    cube1.getMaterial().setDefaultColor(Color::Purple);
    cube2.getMaterial().setDefaultColor(Color::Blue);

    grp1.add(&cube1);
    grp1.add(&cube2);

    Camera camera = Camera();
    camera.setScreenSize(1920, 1080);
    camera.setPosition(glm::vec3(-2, 0, 0));
    camera.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    counter.start();
    
    while (!window.shouldClose()) {
        window.processInput();

        counter.calculateFPS();
        float delta = 1.0f / counter.getFPS();
        // Code de rendu OpenGL
        glm::vec3 rotateValueCube1 = cube1.getRotation();
        glm::vec3 rotateValueCube2 = cube2.getRotation();
        glm::vec3 rotateValue = grp1.getRotation();

        rotateValueCube1.y += (360.0f / 10.0f) * delta;
        rotateValueCube1.x += (360.0f / 10.0f) * delta;

        rotateValueCube2.y += (360.0f / 10.0f) * delta;
        rotateValueCube2.x += (360.0f / 10.0f) * delta;

        rotateValue.x += (360.0f / 10.0f) * delta;
        // rotateValue.y += (360.0f / 10.0f) * delta;
        // rotateValue.z += (360.0f / 10.0f) * delta;

        cube1.setRotation(rotateValueCube1);
        cube2.setRotation(rotateValueCube2);
        grp1.setRotation(rotateValue);

        renderer.render(camera, grp1);

        window.swapBuffersAndPollEvents();
    }

    return 0;
}