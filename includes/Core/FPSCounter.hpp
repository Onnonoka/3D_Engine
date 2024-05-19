#pragma once

#include <iostream>
#include <chrono>

/**
 * @brief Class for counting Frames Per Second (FPS).
 */
class FPSCounter {
public:
    /**
     * @brief Starts the FPS counter by initializing the starting time.
     */
    void start();

    /**
     * @brief Calculates the FPS based on the time elapsed since the last calculation.
     */
    void calculateFPS();

    /**
     * @brief Gets the current FPS count.
     * @return The current FPS count.
     */
    int getFPS();

    /**
     * @brief Sets the initial refresh rate for the FPS counter.
     * @param initialFPS The initial refresh rate to set.
     */
    void setInitialFPS(int initialFPS);
    
    /**
     * @brief Calculates the time difference between the last two frames.
     * @return The time difference between the last two frames.
     */
    float delta() const;

private:
    int frameCount = 0;                                         ///< Frame counter.
    int fps = 75;                                               ///< Current FPS count.
    std::chrono::high_resolution_clock::time_point lastTime;    ///< Last time recorded for FPS.
};