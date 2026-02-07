//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_INPUT_H
#define SUNSETCRAFT_INPUT_H

namespace SunsetEngine
{
    struct Input
    {
        static bool IsKeyPress(unsigned int key);
        static bool IsMouseButtonClick(unsigned int button);
        static glm::vec2 GetMousePosition();
    };

    struct Event
    {
        enum class Action
        {
            Press,
            Release,
            Hold
        };

        struct KeyEvent
        {
            unsigned int key;
            Action action;
        };

        struct MouseEvent
        {
            double x, y;
        };

        using Type = std::variant<KeyEvent, MouseEvent>;
    };

    struct InputManager
    {
        // Take a path to a .json with the key in it.
        static void Init(const std::string_view& Path);
        static bool IsKeyPress(const std::string_view& name, const Event::KeyEvent& event);
        static bool HandleKey(const std::string_view& name, const Event::KeyEvent& event, const std::function<void(const Event::Action& action)>& func);
    };
}

#endif //SUNSETCRAFT_INPUT_H