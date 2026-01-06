//
// Created by sunvy on 02/01/2026.
//

#ifndef SUNSETCRAFT_RAYCASTHIT_H
#define SUNSETCRAFT_RAYCASTHIT_H

#include "Block.h"

enum class BlockId : uint8_t;
class Chunk;

struct RaycastHit
{
    bool Hit = false;
    BlockId BlockType = BlockId::Null;
    Chunk* chunk = nullptr;
    glm::ivec3 blockPose;
    glm::ivec3 hitNormal;

    operator bool() const
    {
        return Hit;
    }

    void Clear()
    {
        Hit = false;
        BlockType = BlockId::Null;
        chunk = nullptr;
        blockPose = glm::ivec3(0);
        hitNormal = glm::ivec3(0);
    }
};

#endif //SUNSETCRAFT_RAYCASTHIT_H