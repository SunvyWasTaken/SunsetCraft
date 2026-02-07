//
// Created by sunvy on 15/12/2025.
//

#include "Input.h"

#include "Render/Renderer.h"

#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>

namespace
{
    glm::vec2 lastMousePosition = glm::vec2(0.0f, 0.0f);
    std::map<unsigned int, bool> bIsMouseButtonClick;

    std::unordered_map<std::string, unsigned int> keyMap;

    void ProcessInputs(const nlohmann::json& inputs)
    {
        if (inputs.empty())
            return;

        for (const auto& input : inputs)
        {
            keyMap.emplace(input["name"], input["key"]);
        }
    }
}

namespace SunsetEngine
{
    bool Input::IsKeyPress(const unsigned int key)
    {
        return glfwGetKey(static_cast<GLFWwindow*>(Renderer::Get()), key) == GLFW_PRESS;
    }

    bool Input::IsMouseButtonClick(const unsigned int button)
    {
        if (glfwGetMouseButton(static_cast<GLFWwindow*>(Renderer::Get()), button) == GLFW_PRESS)
        {
            if (bIsMouseButtonClick.find(button) != bIsMouseButtonClick.end())
            {
                if (!bIsMouseButtonClick[button])
                {
                    bIsMouseButtonClick[button] = true;
                    return true;
                }
                return false;
            }
        }
        bIsMouseButtonClick[button] = false;
        return false;
    }

    glm::vec2 Input::GetMousePosition()
    {
        double x, y;
        glfwGetCursorPos(static_cast<GLFWwindow*>(Renderer::Get()), &x, &y);
        glm::vec2 delta = glm::vec2(x, y) - lastMousePosition;
        lastMousePosition = glm::vec2(x, y);
        return delta;
    }

    void InputManager::Init(const std::string_view& Path)
    {
        const nlohmann::json j = UtilityFunction::LoadJson(Path);

        ProcessInputs(j);
    }

    bool InputManager::IsKeyPress(const std::string_view& name, const Event::KeyEvent& event)
    {
        if (keyMap.contains(name.data()))
        {
            return event.key == keyMap.at(name.data());
        }
        return false;
    }

    bool InputManager::HandleKey(const std::string_view& name, const Event::KeyEvent& event,
        const std::function<void(const Event::Action& action)>& func)
    {
        if (keyMap.contains(name.data()))
        {
            func(event.action);
            return true;
        }
        return false;
    }
}
