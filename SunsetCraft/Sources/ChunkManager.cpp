//
// Created by sunvy on 15/12/2025.
//

#include "ChunkManager.h"

#include "Chunk.h"
#include "CraftScene.h"

namespace
{
    int m_RenderDistance = 2;
    int verticalRadius = 1;

    struct triplet_hash {
        std::size_t operator()(const std::tuple<int,int,int>& t) const
        {
            auto h1 = std::hash<int>{}(std::get<0>(t));
            auto h2 = std::hash<int>{}(std::get<1>(t));
            auto h3 = std::hash<int>{}(std::get<2>(t));
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };

    std::unordered_map<std::tuple<int, int, int>, std::unique_ptr<Chunk>, triplet_hash> m_Chunks;

    template <typename T>
    int WorldToChunk(T value)
    {
        return static_cast<int>(std::floor(value / 32));
    }

    void LoadChunk(const glm::ivec3& position)
    {
        for (int x = position.x - m_RenderDistance; x <= position.x + m_RenderDistance; ++x) {
            for (int z = position.z - m_RenderDistance; z <= position.z + m_RenderDistance; ++z) {
                for (int y = position.y - verticalRadius; y <= position.y + verticalRadius; ++y) {
                    std::tuple<int,int,int> key = std::make_tuple(x, y, z);
                    if (m_Chunks.find(key) == m_Chunks.end()) {
                        // Créer et générer le chunk
                        m_Chunks[key] = std::make_unique<Chunk>(glm::vec3{x, y, z});
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
    LoadChunk(positionInChunk);
}

void ChunkManager::Draw(CraftScene* scene) const
{
    for (const auto& chunk : m_Chunks | std::views::values)
    {
        chunk->UseShader(scene->m_Camera);
        scene->m_TexturesManager.Use(chunk->GetShader());
        chunk->Draw();
    }
}

std::vector<Chunk*> ChunkManager::GetNearbyChunks(const glm::vec3& position)
{
    std::vector<Chunk*> result;

    // Position du joueur en coordonnées chunk
    int chunkX = WorldToChunk(position.x);
    int chunkY = WorldToChunk(position.y);
    int chunkZ = WorldToChunk(position.z);

    constexpr int radius = 1;

    for (int x = chunkX - radius; x <= chunkX + radius; ++x)
    {
        for (int y = chunkY - radius; y <= chunkY + radius; ++y)
        {
            for (int z = chunkZ - radius; z <= chunkZ + radius; ++z)
            {
                auto key = std::make_tuple(x, y, z);
                auto it = m_Chunks.find(key);

                if (it != m_Chunks.end())
                {
                    result.push_back(it->second.get());
                }
            }
        }
    }

    return result;
}
