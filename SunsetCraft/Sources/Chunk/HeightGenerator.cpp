//
// Created by sunvy on 22/01/2026.
//

#include "HeightGenerator.h"

#include "Chunk.h"
#include "Utility/BlockRegistry.h"
#include "Utility/Random.h"

namespace
{
    SunsetEngine::Fbm<SunsetEngine::PerlinNoise<int>, 5, 0.05f> noise{69};
}

void HeightGenerator::SetHeight(Chunk &chunk)
{
    for (int z = 0; z < m_chunkSize; ++z)
        for (int x = 0; x < m_chunkSize; ++x)
        {
            int worldX = x + chunk.GetPosition().x * m_chunkSize;
            int worldZ = z + chunk.GetPosition().z * m_chunkSize;

            float height = noise(worldX, worldZ) * std::visit([]<typename T0>(T0&& val)->float
            {
                if constexpr (!std::is_same_v<std::decay_t<T0>, std::monostate>)
                    return val.amp;
                return 0.f;
            }, chunk.GetBiomeType());

            int terrainH = std::floor(height);

            for (int y = 0; y < m_chunkSize; ++y)
            {
                int worldY = y + chunk.GetPosition().y * m_chunkSize;

                if (worldY > terrainH)
                    chunk.data[Index(x, y, z)] = BlockRegistry::AIR;
                else if (worldY >= terrainH - 1)
                    chunk.data[Index(x, y, z)] = BlockRegistry::GRASS;
                else if (worldY >= terrainH - 3)
                    chunk.data[Index(x, y, z)] = BlockRegistry::DIRT;
                else
                    chunk.data[Index(x, y, z)] = BlockRegistry::STONE;
            }
        }
}
