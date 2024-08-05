#include <GLFW/glfw3.h>
#include "Simulation.h"
#include <time.h>

int main() {
    if (!glfwInit()) {
        // Handle GLFW initialization error
        return -1;
    }
    srand(time(0));


    // Configure GLFW window properties
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    float ratio = 15.0f / 9.0f;
    int width = 1200;
    int height = width / ratio;

    // Create the GLFW window
    GLFWwindow* window = glfwCreateWindow(width, height, "Physics Simulation", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        // Handle window creation error
        return -1;
    }

    glfwMakeContextCurrent(window);

    float fps = 60.0f;

    // Create and run the simulation
    Simulation simulation(window, 1.0 / fps);
    simulation.run();

    glfwTerminate();
    return 0;
}