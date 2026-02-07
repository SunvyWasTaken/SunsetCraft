//
// Created by sunvy on 04/01/2026.
//

#ifndef SUNSETCRAFT_LOGGER_H
#define SUNSETCRAFT_LOGGER_H

#include <spdlog/spdlog.h>

namespace SunsetEngine
{
    class Application;

    struct Log
    {
        friend Application;
    private:
        static void Init();

        static void Shutdown();
    public:
        static std::shared_ptr<spdlog::logger> InitLog(const std::string_view& name);

        static std::shared_ptr<spdlog::logger> GetLogger(std::string name);
    };
}

#define INITLOG(name) SunsetEngine::Log::InitLog(name);
#define LOG(name, level, txt, ...) SunsetEngine::Log::GetLogger(name)->level(std::format(txt, ##__VA_ARGS__));

#endif //SUNSETCRAFT_LOGGER_H