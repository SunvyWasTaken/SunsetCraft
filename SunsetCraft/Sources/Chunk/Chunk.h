//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_CHUNK_H
#define SUNSETCRAFT_CHUNK_H

#include "BiomeType.h"
#include "World/Block.h"

namespace SunsetEngine
{
    class Camera;
    class Shader;
    class Drawable;
}

class CraftScene;

constexpr static int m_chunkSize = 16;
constexpr static int m_CubeChunkSize = m_chunkSize * m_chunkSize * m_chunkSize;

extern std::size_t Index(const int x, const int y, const int z);

using BlockList = std::array<BlockId, m_CubeChunkSize>;

class Chunk final
{
    friend class HeightGenerator;
public:
    Chunk(const glm::ivec3& pos);
    ~Chunk();

    void Draw() const;

    BlockId GetBlockId(const glm::ivec3& pos) const;

    void SetBlockId(const glm::ivec3& pos, BlockId blockId);

    glm::ivec3 GetPosition() const;

    const BlockList& GetBlocks() const;

    void UpdateDrawable(const std::vector<std::uint32_t>& vertices);

    const BiomeType::Type& GetBiomeType() const;

    void SetBiomeType(const BiomeType::Type& biomeType);

    bool bIsDirty;

private:
    glm::ivec3 position;
    BlockList data;

    BiomeType::Type m_BiomeType;

    std::unique_ptr<SunsetEngine::Drawable> m_Drawable;
};

#endif //SUNSETCRAFT_CHUNK_H