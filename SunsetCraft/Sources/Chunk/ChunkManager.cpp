//
// Created by sunvy on 15/12/2025.
//

#include "ChunkManager.h"

#include "Chunk.h"
#include "ChunkMeshBuilder.h"
#include "ChunkUtility.h"
#include "WorldGenerator.h"
#include "Render/RenderCommande.h"
#include "Render/Shader.h"
#include "World/CraftScene.h"

namespace
{
    int m_RenderDistance = 6;
    int verticalRadius = 4;

    std::unordered_map<glm::ivec3, std::unique_ptr<Chunk>, triplet_hash> m_Chunks;
    std::shared_ptr<SunsetEngine::Shader> m_ChunkShader = nullptr;

    template <typename T>
    int WorldToChunk(T value)
    {
        return static_cast<int>(std::floor(value / m_chunkSize));
    }

    void LoadChunk(const glm::ivec3& position)
    {

        for (int x = position.x - m_RenderDistance; x <= position.x + m_RenderDistance; ++x)
        {
            for (int z = position.z - m_RenderDistance; z <= position.z + m_RenderDistance; ++z)
            {
                for (int y = position.y - verticalRadius; y <= position.y + verticalRadius; ++y)
                {
                    const glm::ivec3 key{x, y, z};
                    if (m_Chunks.find(key) == m_Chunks.end())
                    {
                        // Créer et générer le chunk
                        m_Chunks[key] = std::make_unique<Chunk>(glm::vec3{x, y, z});
                        m_Chunks[key]->SetShader(m_ChunkShader);
                        WorldGenerator::Request(*(m_Chunks[key].get()));
                    }
                    // Todo : get le chunk et lui send ça distance au player.
                    // m_Drawable->m_Material->Set<float>("Distance", distance);
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
    LOG("SunsetCraft", info, "Chunk Manager Create")
    WorldGenerator::Init();
    m_Chunks.clear();
    m_ChunkShader = std::make_unique<SunsetEngine::Shader>("SunsetCraft/Shaders/ChunkVertShader.vert", "SunsetCraft/Shaders/ChunkFragShader.frag");
}

void ChunkManager::Shutdown()
{
    WorldGenerator::Shutdown();
    m_Chunks.clear();
    m_ChunkShader.reset();

    LOG("SunsetCraft", info, "Chunk Manager Destroy")
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

void ChunkManager::Render(const SunsetEngine::Camera& camera)
{
    SunsetEngine::Frustum f = camera.GetFrustum();

    for (const std::unique_ptr<Chunk>& chunk: m_Chunks | std::views::values)
    {
        if (chunk->IsEmpty())
            continue;

        if (f.IsVisible(chunk->GetAABB()))
            SunsetEngine::RenderCommande::Submit(*chunk);
    }
}
