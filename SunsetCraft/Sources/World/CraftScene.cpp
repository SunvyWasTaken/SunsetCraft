//
// Created by sunvy on 03/01/2026.
//

#include "CraftScene.h"

#include <filesystem>

#include "RaycastHit.h"
#include "Chunk/Chunk.h"
#include "Block.h"

void CraftScene::LineTrace(RaycastHit& hit, const glm::vec3& start, const glm::vec3& forward, const float distance)
{
    glm::vec3 dir = forward;
    glm::ivec3 block = glm::floor(start);
    HUD("Forward : {}", dir);
    HUD("Start : {}", block);

    glm::ivec3 step;
    step.x = (dir.x > 0) ? 1 : (dir.x < 0 ? -1 : 0);
    step.y = (dir.y > 0) ? 1 : (dir.y < 0 ? -1 : 0);
    step.z = (dir.z > 0) ? 1 : (dir.z < 0 ? -1 : 0);
    HUD("Step : {}", step);

    // Calculer tMax et tDelta
    glm::vec3 tMax;
    glm::vec3 tDelta;

    tMax.x = (dir.x != 0) ? ((step.x > 0 ? (block.x + 1) - start.x : start.x - block.x) / std::abs(dir.x)) : 1e30f;
    tMax.y = (dir.y != 0) ? ((step.y > 0 ? (block.y + 1) - start.y : start.y - block.y) / std::abs(dir.y)) : 1e30f;
    tMax.z = (dir.z != 0) ? ((step.z > 0 ? (block.z + 1) - start.z : start.z - block.z) / std::abs(dir.z)) : 1e30f;

    tDelta.x = (dir.x != 0) ? 1.0f / std::abs(dir.x) : 1e30f;
    tDelta.y = (dir.y != 0) ? 1.0f / std::abs(dir.y) : 1e30f;
    tDelta.z = (dir.z != 0) ? 1.0f / std::abs(dir.z) : 1e30f;

    float t = 0.0f;

    while (t <= distance)
    {
        // Vérifier le bloc courant
        Chunk* chunk = m_Chunks.GetChunks(block);
        if (chunk)
        {
            BlockId blockId = chunk->GetBlockId(block);
            if (blockId != BlockId::Air)
            {
                hit.Hit = true;
                hit.blockPose = block;
                HUD("BlockPos : {}", block);
                hit.BlockType = blockId;
                hit.chunk = chunk;
                return;
            }
        }

        // Avancer vers le prochain bloc
        if (tMax.x < tMax.y)
        {
            if (tMax.x < tMax.z)
            {
                block.x += step.x;
                t = tMax.x;
                tMax.x += tDelta.x;
            }
            else
            {
                block.z += step.z;
                t = tMax.z;
                tMax.z += tDelta.z;
            }
        }
        else
        {
            if (tMax.y < tMax.z)
            {
                block.y += step.y;
                t = tMax.y;
                tMax.y += tDelta.y;
            }
            else
            {
                block.z += step.z;
                t = tMax.z;
                tMax.z += tDelta.z;
            }
        }
    }
}
