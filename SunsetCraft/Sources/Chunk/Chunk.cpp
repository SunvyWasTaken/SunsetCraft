//
// Created by sunvy on 15/12/2025.
//

#include "Chunk.h"

#include "Math/AABB.h"
#include "Render/Camera.h"
#include "Render/Drawable.h"
#include "Render/Shader.h"

#include <glm/gtc/noise.hpp>

#include "../World/CraftScene.h"
#include "World/Block.h"

namespace
{
    CraftScene* m_Scene = nullptr;

    enum VoxelSide : std::uint8_t
    {
        PosX = 0,
        NegX = 1,
        PosY = 2,
        NegY = 3,
        PosZ = 4,
        NegZ = 5
    };

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

    std::size_t Index(const int x, const int y, const int z)
    {
        int N = Chunk::ChunkSize();
        int ix = (x % N + N) % N;
        int iy = (y % N + N) % N;
        int iz = (z % N + N) % N;

        return ix + iz * N + iy * N * N;
    }

    glm::ivec3 WorldToChunk(const glm::ivec3& ChunkPos, const glm::ivec3& pos)
    {
        glm::ivec3 localPos = pos - ChunkPos * Chunk::ChunkSize();

        // s'assure que le résultat est toujours dans [0, ChunkSize-1]
        localPos.x = (localPos.x % Chunk::ChunkSize() + Chunk::ChunkSize()) % Chunk::ChunkSize();
        localPos.y = (localPos.y % Chunk::ChunkSize() + Chunk::ChunkSize()) % Chunk::ChunkSize();
        localPos.z = (localPos.z % Chunk::ChunkSize() + Chunk::ChunkSize()) % Chunk::ChunkSize();

        return localPos;
    }

    bool IsSolid(const BlockList& data, int x, int y, int z)
    {
        if (x < 0 || x >= Chunk::ChunkSize() || y < 0 || y >= Chunk::ChunkSize() || z < 0 || z >= Chunk::ChunkSize())
            return false;
        return data[Index(x, y, z)] != BlockId::Air;
    }

    void CreateMesh(const BlockList& data, std::vector<std::uint32_t>& indices, CraftScene* scene)
    {
        indices.reserve(data.size());
        for (int y = 0; y < Chunk::ChunkSize(); ++y)
        {
            for (int z = 0; z < Chunk::ChunkSize(); ++z)
            {
                for (int x = 0; x < Chunk::ChunkSize(); ++x)
                {
                    const BlockId voxel = data[Index(x, y, z)];
                    if (voxel == BlockId::Air)
                        continue;

                    auto getUv = [&](VoxelSide side)
                    {
                        if (voxel == BlockId::Stone)
                            return scene->m_TexturesManager.Get("stone.png");
                        // exemple : herbe
                        if (side == PosY)
                            return scene->m_TexturesManager.Get("grass_block_top.png");
                        if (side == NegY)
                            return scene->m_TexturesManager.Get("dirt.png");

                        return scene->m_TexturesManager.Get("grass_block_side.png");
                    };

                    // +X
                    if (!IsSolid(data, x + 1, y, z))
                        indices.push_back(EncodeVoxel(x, y, z, PosX, getUv(PosX)));
                    // -X
                    if (!IsSolid(data, x - 1, y, z))
                        indices.push_back(EncodeVoxel(x, y, z, NegX, getUv(NegX)));
                    // +Y
                    if (!IsSolid(data, x, y + 1, z))
                        indices.push_back(EncodeVoxel(x, y, z, PosY, getUv(PosY)));
                    // -Y
                    if (!IsSolid(data, x, y - 1, z))
                        indices.push_back(EncodeVoxel(x, y, z, NegY, getUv(NegY)));
                    // +Z
                    if (!IsSolid(data, x, y, z + 1))
                        indices.push_back(EncodeVoxel(x, y, z, PosZ, getUv(PosZ)));
                    // -Z
                    if (!IsSolid(data, x, y, z - 1))
                        indices.push_back(EncodeVoxel(x, y, z, NegZ, getUv(NegZ)));
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

    // Fonction pseudo-aléatoire basée sur x, z et seed
    float hash(int x, int z, int seed) {
        int n = x + z * 57 + seed * 131;
        n = (n << 13) ^ n;
        return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
    }

    // Fonction de lissage (smoothstep)
    float smoothStep(float t) {
        return t * t * (3 - 2 * t);
    }

    // Interpolation bilinéaire lissée
    float lerp(float a, float b, float t) {
        return a + (b - a) * smoothStep(t);
    }

    // Noise chaotique mais lisse
    float smoothChaosNoise(float x, float z, int seed)
    {
        int x0 = (int)std::floor(x);
        int x1 = x0 + 1;
        int z0 = (int)std::floor(z);
        int z1 = z0 + 1;

        float sx = x - (float)x0;
        float sz = z - (float)z0;

        float n0 = hash(x0, z0, seed);
        float n1 = hash(x1, z0, seed);
        float ix0 = lerp(n0, n1, sx);

        n0 = hash(x0, z1, seed);
        n1 = hash(x1, z1, seed);
        float ix1 = lerp(n0, n1, sx);

        return lerp(ix0, ix1, sz);
    }
}

Chunk::Chunk(const glm::vec3& pos, CraftScene* scene)
    : position(pos)
    , data()
    , m_Drawable(nullptr)
    , m_Shader(nullptr)
{
    Generate();

    m_Scene = scene;

    std::vector<std::uint32_t> vertices;
    CreateMesh(data, vertices, m_Scene);

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
            const float noise = smoothChaosNoise(WorldX * 0.05, WorldZ * 0.05, seed) * 20;
            //const float noise = smoothNoise(WorldX, WorldZ, seed) * 20;
            //const float noise = glm::perlin(glm::vec2{WorldX, WorldZ}) * 20;

            for (int y = 0; y < Chunk::ChunkSize(); ++y)
            {
                int WorldY = y + static_cast<int>(position.y) * m_chunkSize;
                if (WorldY < noise - 2)
                    data[Index(x, y, z)] = BlockId::Stone;
                else if (WorldY < noise)
                    data[Index(x, y, z)] = BlockId::Dirt;
                else
                    data[Index(x, y, z)] = BlockId::Air;
            }
        }
    }
}

SunsetEngine::Shader* Chunk::GetShader()
{
    return m_Shader.get();
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
    std::vector<std::uint32_t> vertices;
    CreateMesh(data, vertices, m_Scene);

    m_Drawable->Clear();
    m_Drawable->Create(vertices);
}
