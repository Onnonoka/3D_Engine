#include <Basic/FPSCounter.hpp>


void FPSCounter::start() {
    lastTime = std::chrono::high_resolution_clock::now();
}

void FPSCounter::calculateFPS() {
    frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime).count();

    if (duration >= 1) {
        fps = frameCount;
        frameCount = 0;
        lastTime = currentTime;
        std::cout << "FPS: " << fps << std::endl;
    }
}

int FPSCounter::getFPS() {
    return fps;
}

void FPSCounter::setInitialFPS(int initialFPS) {
    fps = initialFPS;
}