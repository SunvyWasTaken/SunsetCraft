//
// Created by sunvy on 03/01/2026.
//

#ifndef SUNSETCRAFT_BLOCK_H
#define SUNSETCRAFT_BLOCK_H

enum class BlockId : uint8_t
{
    Null    = 0,
    Air     = 1,
    Dirt    = 2,
    Grass   = 3,
    Stone   = 4
};

enum class BlockFace : uint8_t
{
    East    = 0, // +X
    West    = 1, // -X
    Top     = 2, // +Y
    Bottom  = 3, // -Y
    North   = 4, // +Z
    South   = 5  // -Z
};

struct BlockType
{
    BlockId id = BlockId::Null;
    std::string name = "unknow";
    std::array<std::string, 6> textures = {"SunsetShimmer.png", "SunsetShimmer.png", "SunsetShimmer.png", "SunsetShimmer.png", "SunsetShimmer.png", "SunsetShimmer.png"};
    bool IsSolid = false;
};

#endif //SUNSETCRAFT_BLOCK_H