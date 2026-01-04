//
// Created by sunvy on 04/01/2026.
//

#include "Logger.h"

namespace
{
    // Logger
    std::vector<std::string> m_Logger;
    // Hud
    std::vector<std::string> m_Texts;
}

namespace SunsetEngine
{
    void Logger::Add(std::string txt)
    {
        m_Logger.emplace_back(txt);
    }

    std::vector<std::string>::iterator Logger::begin()
    {
        return m_Logger.begin();
    }

    std::vector<std::string>::iterator Logger::end()
    {
        return m_Logger.end();
    }

    void Hud::Add(const std::string& msg)
    {
        m_Texts.emplace_back(msg);
    }

    void Hud::Clear()
    {
        m_Texts.clear();
    }

    bool Hud::IsEmpty()
    {
        return m_Texts.empty();
    }

    std::vector<std::string>::iterator Hud::begin()
    {
        return m_Texts.begin();
    }

    std::vector<std::string>::iterator Hud::end()
    {
        return m_Texts.end();
    }
}
