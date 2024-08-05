#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include "RigidBody.h"

#define IRL_TO_GL_RATIO 287.46e-14f

class Renderer {
public:
    Renderer(GLFWwindow* window);

    void render(const std::vector<RigidBody>& bodies);
    float toGL(float x);

private:
    GLFWwindow* window;
};
