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
    void InputRegister::Init(const std::string_view& Path)
    {
        const nlohmann::json j = UtilityFunction::LoadJson(Path);

        ProcessInputs(j);
    }

    void InputRegister::OnEvent(const Event::Type& event)
    {
        std::visit(overloads{
        [](const Event::KeyEvent& event)
        {

        }, [](const Event::MouseEvent& event)
        {

        }}, event);
    }

    glm::vec2 InputRegister::GetMouseDelta()
    {
        double x, y;
        glfwGetCursorPos(static_cast<GLFWwindow*>(Renderer::Get()), &x, &y);
        glm::vec2 delta = glm::vec2(x, y) - lastMousePosition;
        lastMousePosition = glm::vec2(x, y);
        return delta;
    }

    bool InputRegister::IsKeyPress(const std::string_view& name)
    {
        if (!keyMap.contains(name.data()))
            return false;
        return glfwGetKey(static_cast<GLFWwindow*>(Renderer::Get()), keyMap[name.data()]);
    }

    void InputRegister::RegisterAction(const std::string_view& name,
        const std::function<void(const Event::Action&)>& func)
    {
    }
}
