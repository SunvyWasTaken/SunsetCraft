//
// Created by sunvy on 22/01/2026.
//

#ifndef SUNSETCRAFT_BIOMEGENERATOR_H
#define SUNSETCRAFT_BIOMEGENERATOR_H

#include "BiomeType.h"

struct BiomeGenerator
{
    static BiomeType::Type RequestBiome(const glm::ivec2& coord);
};

#endif //SUNSETCRAFT_BIOMEGENERATOR_H