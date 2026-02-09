//
// Created by sunvy on 15/12/2025.
//

#include "Chunk.h"

#include "Render/Drawable.h"
#include "Render/Shader.h"

namespace
{
    constexpr std::uint32_t EncodeVoxel(
        const std::uint32_t x,
        const std::uint32_t y,
        const std::uint32_t z,
        const std::uint8_t side,
        const std::uint32_t uvID)
    {
        return  (x & 0x1F) |
                ((y & 0x1F) << 5) |
                ((z & 0x1F) << 10) |
                ((side & 0x7) << 15) |
                ((uvID & 0x1FF) << 23);
    }

    glm::ivec3 WorldToChunk(const glm::ivec3& ChunkPos, const glm::ivec3& pos)
    {
        glm::ivec3 localPos = pos - ChunkPos * m_chunkSize;

        // s'assure que le résultat est toujours dans [0, ChunkSize-1]
        localPos.x = (localPos.x % m_chunkSize + m_chunkSize) % m_chunkSize;
        localPos.y = (localPos.y % m_chunkSize + m_chunkSize) % m_chunkSize;
        localPos.z = (localPos.z % m_chunkSize + m_chunkSize) % m_chunkSize;

        return localPos;
    }

    bool IsInside(const glm::ivec3& chunkPos, const glm::ivec3& pos)
    {
        constexpr int HalfChunkSize = m_chunkSize / 2;
        return chunkPos.x - HalfChunkSize <= pos.x && chunkPos.x - HalfChunkSize >= pos.x &&
            chunkPos.y - HalfChunkSize <= pos.y && chunkPos.y - HalfChunkSize >= pos.y &&
            chunkPos.z - HalfChunkSize <= pos.z && chunkPos.z - HalfChunkSize >= pos.z;
    }
}

/****************************************/
/* CHUNK                                */
/****************************************/

std::size_t Index(const int x, const int y, const int z)
{
    int N = m_chunkSize;
    int ix = (x % N + N) % N;
    int iy = (y % N + N) % N;
    int iz = (z % N + N) % N;

    return ix + iz * N + iy * N * N;
}

Chunk::Chunk(const glm::ivec3& pos)
    : bIsDirty(true)
    , position(pos)
    , data()
    , m_Drawable(std::make_unique<SunsetEngine::Drawable>())
{
}
static int nbrShaderCopy = 0;
Chunk::~Chunk()
{
    --nbrShaderCopy;
}

BlockId Chunk::GetBlockId(const glm::ivec3& pos) const
{
    const glm::ivec3 i = WorldToChunk(position, pos);
    return data[Index(i.x, i.y, i.z)];
}

// pos is the world location
void Chunk::SetBlockId(const glm::ivec3& pos, BlockId blockId)
{
    const glm::ivec3 i = WorldToChunk(position, pos);
    data[Index(i.x, i.y, i.z)] = blockId;
}

glm::ivec3 Chunk::GetPosition() const
{
    return position;
}

const BlockList & Chunk::GetBlocks() const
{
    return data;
}

const BiomeType::Type& Chunk::GetBiomeType() const
{
    return m_BiomeType;
}

void Chunk::SetBiomeType(const BiomeType::Type &biomeType)
{
    m_BiomeType = biomeType;
}

void Chunk::SetShader(const std::shared_ptr<SunsetEngine::Shader>& shader)
{
    LOG("SunsetCraft", trace, "nbr copy {}", ++nbrShaderCopy);
    m_Drawable->m_Shader = shader;
}

Chunk::operator const SunsetEngine::Drawable&() const
{
    return *m_Drawable;
}
