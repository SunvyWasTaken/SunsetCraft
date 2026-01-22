//
// Created by sunvy on 21/01/2026.
//

#include "ChunkMeshBuilder.h"

#include "Chunk.h"
#include "ChunkUtility.h"
#include "Render/Drawable.h"
#include "Utility/BlockRegistry.h"
#include "World/CraftScene.h"

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
    
    bool IsSolid(const BlockList& data, int x, int y, int z)
    {
        if (x < 0 || x >= m_chunkSize || y < 0 || y >= m_chunkSize || z < 0 || z >= m_chunkSize)
            return false;
        return data[Index(x, y, z)] != BlockRegistry::AIR;
    }
    
    void CreateMesh(const BlockList& data, std::vector<std::uint32_t>& indices)
    {
        indices.reserve(data.size());
        for (int z = 0; z < m_chunkSize; ++z)
        {
            for (int x = 0; x < m_chunkSize; ++x)
            {
                for (int y = 0; y < m_chunkSize; ++y)
                {
                    const BlockId voxel = data[Index(x, y, z)];
                    if (voxel == BlockRegistry::AIR)
                        continue;

                    auto getUv = [&](BlockFace side)
                    {
                        const BlockType& block = BlockRegistry::Get(voxel);
                        return TexturesManager::Get(block.textures[static_cast<uint8_t>(side)]);
                    };

                    // +X
                    if (!IsSolid(data, x + 1, y, z))
                        indices.push_back(EncodeVoxel(x, y, z, static_cast<uint8_t>(BlockFace::East), getUv(BlockFace::East)));
                    // -X
                    if (!IsSolid(data, x - 1, y, z))
                        indices.push_back(EncodeVoxel(x, y, z, static_cast<uint8_t>(BlockFace::West), getUv(BlockFace::West)));
                    // +Y
                    if (!IsSolid(data, x, y + 1, z))
                        indices.push_back(EncodeVoxel(x, y, z, static_cast<uint8_t>(BlockFace::Top), getUv(BlockFace::Top)));
                    // -Y
                    if (!IsSolid(data, x, y - 1, z))
                        indices.push_back(EncodeVoxel(x, y, z, static_cast<uint8_t>(BlockFace::Bottom), getUv(BlockFace::Bottom)));
                    // +Z
                    if (!IsSolid(data, x, y, z + 1))
                        indices.push_back(EncodeVoxel(x, y, z, static_cast<uint8_t>(BlockFace::North), getUv(BlockFace::North)));
                    // -Z
                    if (!IsSolid(data, x, y, z - 1))
                        indices.push_back(EncodeVoxel(x, y, z, static_cast<uint8_t>(BlockFace::South), getUv(BlockFace::South)));
                }
            }
        }
    }    
}

void ChunkMeshBuilder::Build(Chunk &chunk)
{
    std::vector<std::uint32_t> vertices;

    CreateMesh(chunk.GetBlocks(), vertices);

    chunk.UpdateDrawable(vertices);
}

