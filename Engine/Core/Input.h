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
        struct KeyEvent
        {
            unsigned int key;
        };

        struct MouseEvent
        {
            float x, y;
        };

        using Type = std::variant<KeyEvent, MouseEvent>;
    };
}

#endif //SUNSETCRAFT_INPUT_H