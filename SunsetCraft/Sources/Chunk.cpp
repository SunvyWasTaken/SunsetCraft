//
// Created by sunvy on 15/12/2025.
//

#include "Chunk.h"

#include "Math/AABB.h"
#include "Render/Camera.h"
#include "Render/Drawable.h"
#include "Render/Shader.h"

#include <glm/gtc/noise.hpp>

#include "CraftScene.h"

namespace
{
    constexpr std::uint32_t EncodeVoxel(
        const std::uint32_t x,
        const std::uint32_t y,
        const std::uint32_t z,
        const std::uint32_t type,
        const std::uint32_t uvID)
    {
        return  (x & 0x1F) |
                ((y & 0x1F) << 5) |
                ((z & 0x1F) << 10) |
                ((type & 0xFF) << 15) |
                ((uvID & 0x1FF) << 23);
    }

    std::size_t Index(const int x, const int y, const int z)
    {
        return x + z * Chunk::ChunkSize() + y * Chunk::ChunkSize() * Chunk::ChunkSize();
    }

    bool IsSolid(const std::array<std::uint8_t, 32*32*32>& data, int x, int y, int z)
    {
        if (x < 0 || x >= Chunk::ChunkSize() || y < 0 || y >= Chunk::ChunkSize() || z < 0 || z >= Chunk::ChunkSize())
            return true;
        return data[Index(x, y, z)] != 0;
    }

    void CreateMesh(const std::array<std::uint8_t, 32*32*32>& data, std::vector<std::uint32_t>& indices, CraftScene* scene)
    {
        indices.reserve(data.size());

        for (int y = 0; y < Chunk::ChunkSize(); ++y)
        {
            for (int z = 0; z < Chunk::ChunkSize(); ++z)
            {
                for (int x = 0; x < Chunk::ChunkSize(); ++x)
                {
                    const std::uint8_t voxel = data[Index(x, y, z)];
                    if (voxel == 0)
                        continue;

                    // Vérifie si au moins un voisin est vide
                    if (IsSolid(data, x+1, y, z) &&
                        IsSolid(data, x-1, y, z) &&
                        IsSolid(data, x, y+1, z) &&
                        IsSolid(data, x, y-1, z) &&
                        IsSolid(data, x, y, z+1) &&
                        IsSolid(data, x, y, z-1))
                    {
                        continue;
                    }

                    std::uint32_t index = EncodeVoxel(x, y, z, voxel, scene->m_TexturesManager.Get("grass_block_side.png"));
                    indices.push_back(index);
                }
            }
        }
    }

    float smoothNoise(int x, int z, int seed)
    {
        float nx = (std::sin(x * 0.1f) + 1.0f) * 0.5f;
        float nz = (std::sin(z * 0.1f) + 1.0f) * 0.5f;
        return nx + nz * 0.5f;
    }
}

Chunk::Chunk(const glm::vec3& pos, CraftScene* scene)
    : position(pos)
    , data()
    , m_Drawable(nullptr)
    , m_Shader(nullptr)
{
    Generate();

    std::vector<std::uint32_t> vertices;
    CreateMesh(data, vertices, scene);

    m_Drawable = std::make_unique<SunsetEngine::Drawable>(vertices);
    m_Shader = std::make_unique<SunsetEngine::Shader>("SunsetCraft/Shaders/ChunkVertShader.vert", "SunsetCraft/Shaders/ChunkFragShader.frag");
}

Chunk::~Chunk()
{
}

void Chunk::UseShader(const SunsetEngine::Camera& camera) const
{
    m_Shader->Use();
    m_Shader->SetMat4("projection", camera.GetProjection());
    m_Shader->SetMat4("view", camera.GetViewMatrix());
    m_Shader->SetVec3("chunkLocation", position);
}

void Chunk::Draw() const
{
    m_Drawable->Draw();
}

void Chunk::Generate()
{
    const float scale = 0.05f;
    const int seed = 56;

    for (int z = 0; z < m_chunkSize; ++z)
    {
        int WorldZ = z + static_cast<int>(position.z) * m_chunkSize;

        for (int x = 0; x < m_chunkSize; ++x)
        {
            int WorldX = x + static_cast<int>(position.x) * m_chunkSize;
            const float noise = smoothNoise(WorldX, WorldZ, seed) * 20;
            // const float noise = glm::perlin(glm::vec2{WorldX, WorldZ}) * 20;

            for (int y = 0; y < Chunk::ChunkSize(); ++y)
            {
                int WorldY = y + static_cast<int>(position.y) * m_chunkSize;
                if (WorldY < noise)
                    data[Index(x, y, z)] = 1;
                else
                    data[Index(x, y, z)] = 0;
            }
        }
    }
}

std::vector<SunsetEngine::AABB> Chunk::GetAABBs(const glm::ivec3& regionMin, const glm::ivec3& regionMax) const
{
    std::vector<SunsetEngine::AABB> solids;
    for (int x = regionMin.x; x <= regionMax.x; ++x)
        for (int y = regionMin.y; y <= regionMax.y; ++y)
            for (int z = regionMin.z; z <= regionMax.z; ++z)
                if (IsSolid(data, x, y, z)) {
                    solids.push_back(SunsetEngine::AABB
                    {
                        glm::vec3(x, y, z),
                        glm::vec3(x + 1.0f, y + 1.0f, z + 1.0f)
                    });
                }
    return solids;
}

SunsetEngine::Shader* Chunk::GetShader()
{
    return m_Shader.get();
}
