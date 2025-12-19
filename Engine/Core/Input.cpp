//
// Created by sunvy on 15/12/2025.
//

#include "Input.h"

#include "Render/Renderer.h"

#include <GLFW/glfw3.h>

namespace
{
    glm::vec2 lastMousePosition = glm::vec2(0.0f, 0.0f);
}

namespace SunsetEngine
{
    bool Input::IsKeyPress(const unsigned int key)
    {
        return glfwGetKey(static_cast<GLFWwindow*>(Renderer::Get()), key) == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition()
    {
        double x, y;
        glfwGetCursorPos(static_cast<GLFWwindow*>(Renderer::Get()), &x, &y);
        glm::vec2 delta = glm::vec2(x, y) - lastMousePosition;
        lastMousePosition = glm::vec2(x, y);
        return delta;
    }
}
