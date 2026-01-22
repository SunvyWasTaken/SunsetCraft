//
// Created by sunvy on 22/01/2026.
//

#include "WorldGenerator.h"

#include "BiomeGenerator.h"
#include "Chunk.h"
#include "ChunkMeshBuilder.h"
#include "HeightGenerator.h"

namespace
{

}

void WorldGenerator::Init()
{
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
