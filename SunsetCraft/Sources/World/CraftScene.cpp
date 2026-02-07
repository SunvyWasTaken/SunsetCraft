//
// Created by sunvy on 03/01/2026.
//

#include "CraftScene.h"

#include "RaycastHit.h"
#include "Chunk/Chunk.h"
#include "Block.h"
#include "Utility/BlockRegistry.h"

CraftScene::CraftScene()
{
    INITLOG("SunsetCraft");
    ChunkManager::Init();
}

CraftScene::~CraftScene()
{
    ChunkManager::Shutdown();
}

void CraftScene::Update(float deltaTime)
{
}

void CraftScene::Render()
{
}

void CraftScene::LineTrace(RaycastHit& hit, const glm::vec3& start, const glm::vec3& forward, const float distance)
{
    return;

    hit.Clear();

    // Direction du rayon
    glm::vec3 dir = glm::normalize(forward);

    // Position voxel courante
    glm::ivec3 voxelPos = glm::floor(start);

    // Sens de progression
    glm::ivec3 step;
    step.x = (dir.x > 0) ? 1 : (dir.x < 0 ? -1 : 0);
    step.y = (dir.y > 0) ? 1 : (dir.y < 0 ? -1 : 0);
    step.z = (dir.z > 0) ? 1 : (dir.z < 0 ? -1 : 0);

    // Distance en t pour traverser un voxel
    glm::vec3 tDelta;
    tDelta.x = (dir.x != 0.0f) ? std::abs(1.0f / dir.x) : FLT_MAX;
    tDelta.y = (dir.y != 0.0f) ? std::abs(1.0f / dir.y) : FLT_MAX;
    tDelta.z = (dir.z != 0.0f) ? std::abs(1.0f / dir.z) : FLT_MAX;

    // Distance jusqu'à la première frontière
    glm::vec3 tMax;
    tMax.x = (dir.x > 0)
        ? (voxelPos.x + 1 - start.x) * tDelta.x
        : (start.x - voxelPos.x) * tDelta.x;

    tMax.y = (dir.y > 0)
        ? (voxelPos.y + 1 - start.y) * tDelta.y
        : (start.y - voxelPos.y) * tDelta.y;

    tMax.z = (dir.z > 0)
        ? (voxelPos.z + 1 - start.z) * tDelta.z
        : (start.z - voxelPos.z) * tDelta.z;

    float t = 0.0f;
    glm::ivec3 hitNormal(0);

    // Boucle DDA
    while (t <= distance)
    {
        // Récupération du chunk / bloc
        // Chunk* chunk = m_Chunks.GetChunks(voxelPos);
        // if (chunk)
        // {
        //     BlockId blockId = chunk->GetBlockId(voxelPos);
        //     if (blockId != BlockRegistry::AIR)
        //     {
        //         hit.Hit = true;
        //         hit.blockPose = voxelPos;
        //         hit.chunk = chunk;
        //         hit.BlockType = blockId;
        //         hit.hitNormal = hitNormal;
        //         return;
        //     }
        // }

        // Avancer vers la frontière la plus proche
        if (tMax.x < tMax.y)
        {
            if (tMax.x < tMax.z)
            {
                voxelPos.x += step.x;
                t = tMax.x;
                tMax.x += tDelta.x;
                hitNormal = glm::ivec3(-step.x, 0, 0);
            }
            else
            {
                voxelPos.z += step.z;
                t = tMax.z;
                tMax.z += tDelta.z;
                hitNormal = glm::ivec3(0, 0, -step.z);
            }
        }
        else
        {
            if (tMax.y < tMax.z)
            {
                voxelPos.y += step.y;
                t = tMax.y;
                tMax.y += tDelta.y;
                hitNormal = glm::ivec3(0, -step.y, 0);
            }
            else
            {
                voxelPos.z += step.z;
                t = tMax.z;
                tMax.z += tDelta.z;
                hitNormal = glm::ivec3(0, 0, -step.z);
            }
        }
    }
}
