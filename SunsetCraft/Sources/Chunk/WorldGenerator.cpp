//
// Created by sunvy on 22/01/2026.
//

#include "WorldGenerator.h"

#include <queue>

#include "BiomeGenerator.h"
#include "Chunk.h"
#include "ChunkMeshBuilder.h"
#include "HeightGenerator.h"

namespace
{
    std::vector<std::thread> workerThreads;

    struct ChunkBuildData
    {
        glm::ivec3 position;
        BlockList data;
        BiomeType biomeType;
    };

    std::mutex queueMutex;
    std::queue<ChunkBuildData> ChunkBuildQueue;

    void SendToWorker(Chunk& chunk)
    {
        std::thread workerThread;
    }
}

void WorldGenerator::Init()
{
    unsigned int threadCount = std::thread::hardware_concurrency();
    LOG("SunsetCraft", info, "thread count {}", threadCount)
}

void WorldGenerator::Shutdown()
{
}

void WorldGenerator::Request(Chunk &chunk)
{
    chunk.SetBiomeType(BiomeGenerator::RequestBiome(chunk.GetPosition()));
    HeightGenerator::SetHeight(chunk);
    ChunkMeshBuilder::Build(chunk);
}
