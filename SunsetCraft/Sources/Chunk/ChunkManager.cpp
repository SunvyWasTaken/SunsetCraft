//
// Created by sunvy on 15/12/2025.
//

#include "ChunkManager.h"

#include "Chunk.h"
#include "../World/CraftScene.h"

namespace
{
    int m_RenderDistance = 6;
    int verticalRadius = 2;

    using ChunkKey = std::tuple<int,int,int>;

    struct triplet_hash
    {
        std::size_t operator()(const ChunkKey& t) const
        {
            auto h1 = std::hash<int>{}(std::get<0>(t));
            auto h2 = std::hash<int>{}(std::get<1>(t));
            auto h3 = std::hash<int>{}(std::get<2>(t));
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };

    std::unordered_map<ChunkKey, std::unique_ptr<Chunk>, triplet_hash> m_Chunks;

    template <typename T>
    int WorldToChunk(T value)
    {
        return static_cast<int>(std::floor(value / m_chunkSize));
    }

    void LoadChunk(const glm::ivec3& position, CraftScene* scene)
    {
        for (int x = position.x - m_RenderDistance; x <= position.x + m_RenderDistance; ++x) {
            for (int z = position.z - m_RenderDistance; z <= position.z + m_RenderDistance; ++z) {
                for (int y = position.y - verticalRadius; y <= position.y + verticalRadius; ++y) {
                    ChunkKey key = std::make_tuple(x, y, z);
                    if (m_Chunks.find(key) == m_Chunks.end()) {
                        // Créer et générer le chunk
                        m_Chunks[key] = std::make_unique<Chunk>(glm::vec3{x, y, z}, scene);
                    }
                }
            }
        }
    }

    void UnloadChunk(const glm::ivec3& position)
    {
        for (auto it = m_Chunks.begin(); it != m_Chunks.end(); )
        {
            int dx = std::abs(std::get<0>(it->first) - position.x);
            int dy = std::abs(std::get<1>(it->first) - position.y);
            int dz = std::abs(std::get<2>(it->first) - position.z);

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

ChunkManager::ChunkManager()
{
    LOG("Chunk Manager Create")
    m_Chunks.clear();
}

ChunkManager::~ChunkManager()
{
    m_Chunks.clear();
}

void ChunkManager::Update(const glm::vec3& position)
{
    const glm::ivec3 positionInChunk{
        WorldToChunk(position.x),
        WorldToChunk(position.y),
        WorldToChunk(position.z)};

    UnloadChunk(positionInChunk);
    LoadChunk(positionInChunk, m_Scene);
}

void ChunkManager::Draw() const
{
    HUD("ChunkManager Draw")
    for (const auto& chunk : m_Chunks | std::views::values)
    {
        chunk->UseShader(m_Scene->m_Camera);
        m_Scene->m_TexturesManager.Use(chunk->GetShader());
        chunk->Draw();
    }
}

Chunk* ChunkManager::GetChunks(const glm::vec3& position)
{
    Chunk* result = nullptr;

    // Position du joueur en coordonnées chunk
    int chunkX = WorldToChunk(position.x);
    int chunkY = WorldToChunk(position.y);
    int chunkZ = WorldToChunk(position.z);

    const ChunkKey key = std::make_tuple(chunkX, chunkY, chunkZ);

    result = m_Chunks.at(key).get();

    return result;
}
