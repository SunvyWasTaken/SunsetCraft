//
// Created by sunvy on 04/01/2026.
//

#ifndef SUNSETCRAFT_LOGGER_H
#define SUNSETCRAFT_LOGGER_H

namespace SunsetEngine
{
    struct Logger
    {
        static void Add(std::string txt);

        static std::vector<std::string>::iterator begin();

        static std::vector<std::string>::iterator end();
    };

    struct Hud
    {
        static void Add(const std::string& msg);

        static void Clear();

        static bool IsEmpty();

        static std::vector<std::string>::iterator begin();
        static std::vector<std::string>::iterator end();
    };
}

#define LOG(txt, ...) SunsetEngine::Logger::Add(std::format(txt, ##__VA_ARGS__));
#define HUD(txt, ...) SunsetEngine::Hud::Add(std::format(txt, ##__VA_ARGS__));

#endif //SUNSETCRAFT_LOGGER_H