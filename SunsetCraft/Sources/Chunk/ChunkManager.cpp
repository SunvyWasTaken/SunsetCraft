//
// Created by sunvy on 15/12/2025.
//

#include "ChunkManager.h"

#include "Chunk.h"
#include "ChunkMeshBuilder.h"
#include "ChunkUtility.h"
#include "WorldGenerator.h"
#include "Render/Shader.h"
#include "World/CraftScene.h"

namespace
{
    int m_RenderDistance = 6;
    int verticalRadius = 2;

    std::unordered_map<glm::ivec3, std::unique_ptr<Chunk>, triplet_hash> m_Chunks;
    std::unique_ptr<SunsetEngine::Shader> m_ChunkShader = nullptr;

    template <typename T>
    int WorldToChunk(T value)
    {
        return static_cast<int>(std::floor(value / m_chunkSize));
    }

    void LoadChunk(const glm::ivec3& position)
    {
        for (int x = position.x - m_RenderDistance; x <= position.x + m_RenderDistance; ++x) {
            for (int z = position.z - m_RenderDistance; z <= position.z + m_RenderDistance; ++z) {
                for (int y = position.y - verticalRadius; y <= position.y + verticalRadius; ++y) {
                    const glm::ivec3 key{x, y, z};
                    if (m_Chunks.find(key) == m_Chunks.end()) {
                        // Créer et générer le chunk
                        m_Chunks[key] = std::make_unique<Chunk>(glm::vec3{x, y, z});
                        WorldGenerator::Request(*(m_Chunks[key].get()));
                    }
                }
            }
        }
    }

    void UnloadChunk(const glm::ivec3& position)
    {
        for (auto it = m_Chunks.begin(); it != m_Chunks.end(); )
        {
            int dx = std::abs(it->first.x - position.x);
            int dy = std::abs(it->first.y - position.y);
            int dz = std::abs(it->first.z - position.z);

            if (dx > m_RenderDistance || dz > m_RenderDistance || dy > verticalRadius)
            {
                it->second.reset();
                it = m_Chunks.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

void ChunkManager::Init()
{
    LOG("Chunk Manager Create")

    m_Chunks.clear();
    m_ChunkShader = std::make_unique<SunsetEngine::Shader>("SunsetCraft/Shaders/ChunkVertShader.vert", "SunsetCraft/Shaders/ChunkFragShader.frag");
}

void ChunkManager::Shutdown()
{
    m_Chunks.clear();
    m_ChunkShader.reset();
}

void ChunkManager::Update(const glm::vec3& position)
{
    const glm::ivec3 positionInChunk{
        WorldToChunk(position.x),
        WorldToChunk(position.y),
        WorldToChunk(position.z)};

    UnloadChunk(positionInChunk);
    LoadChunk(positionInChunk);
}

void ChunkManager::SetBlock(const glm::vec3 &position, BlockType blockType)
{
}

BlockType ChunkManager::GetBlock(const glm::vec3 &position)
{
    return BlockType{};
}

void ChunkManager::Draw(CraftScene* scene)
{
    m_ChunkShader->Use();
    m_ChunkShader->SetMat4("projection", scene->m_Camera.GetProjection());
    m_ChunkShader->SetMat4("view", scene->m_Camera.GetViewMatrix());

    scene->m_TexturesManager.Use(m_ChunkShader.get());

    for (const auto &chunk: m_Chunks | std::views::values)
    {
        m_ChunkShader->SetVec3("chunkLocation", chunk->GetPosition());
        chunk->Draw();
    }
}
