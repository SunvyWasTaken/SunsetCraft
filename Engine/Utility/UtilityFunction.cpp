//
// Created by sunvy on 06/02/2026.
//

#include "UtilityFunction.h"

#include <fstream>
#include <nlohmann/json.hpp>

nlohmann::json SunsetEngine::UtilityFunction::LoadJson(const std::string_view& path)
{
    std::ifstream file;
    file.open(path.data());

    nlohmann::json json;

    if (!file.is_open())
    {
        LOG("Json file couldn't be open")
        return json;
    }

    file >> json;
    return json;
}
