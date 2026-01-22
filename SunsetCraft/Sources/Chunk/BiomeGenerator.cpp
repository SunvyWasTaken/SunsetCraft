//
// Created by sunvy on 22/01/2026.
//

#include "BiomeGenerator.h"

#include "Utility/Random.h"

namespace
{
    SunsetEngine::Fbm<SunsetEngine::PerlinNoise<int>, 5, 0.0512f> HumidityNoise{69};
    SunsetEngine::Fbm<SunsetEngine::PerlinNoise<int>, 5, 0.0512f> HeatNoise{69 + 69};
}

BiomeType::Type BiomeGenerator::RequestBiome(const glm::ivec2 &coord)
{
    BiomeData data{HumidityNoise(coord), HeatNoise(coord)};

    if (data.heat > 0.5)
    {
        if (data.humidity > 0)
            return BiomeType::Ocean{};

        return BiomeType::Desert{};
    }
    else if (data.heat < -0.5)
    {
        // if (data.humidity > 0.7)
            return BiomeType::Mountain{};
    }
    else
    {
        if (data.humidity > 0)
            return BiomeType::Forest{};
        else
            return BiomeType::Plain{};
    }
}
