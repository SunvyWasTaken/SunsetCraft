//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_CHUNK_H
#define SUNSETCRAFT_CHUNK_H

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

using BlockList = std::array<BlockId, m_CubeChunkSize>;

class Chunk
{
public:
    Chunk(const glm::vec3& pos, CraftScene* scene);
    ~Chunk();

    void UseShader(const SunsetEngine::Camera& camera) const;

    void Draw() const;

    void Generate();

    static int ChunkSize()
    {
        return m_chunkSize;
    }

    SunsetEngine::Shader* GetShader();

    BlockId GetBlockId(const glm::ivec3& pos) const;

    void SetBlockId(const glm::ivec3& pos, BlockId blockId);

private:
    glm::vec3 position;
    BlockList data;

    std::unique_ptr<SunsetEngine::Drawable> m_Drawable;
    std::unique_ptr<SunsetEngine::Shader> m_Shader;
};

#endif //SUNSETCRAFT_CHUNK_H