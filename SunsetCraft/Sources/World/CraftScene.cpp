//
// Created by sunvy on 03/01/2026.
//

#include "CraftScene.h"

#include "RaycastHit.h"
#include "Chunk/Chunk.h"
#include "Block.h"

void CraftScene::LineTrace(RaycastHit& hit, const glm::vec3& start, const glm::vec3& end)
{
    const float distance = glm::distance(start, end);
    if (distance <= 0)
        return;

    const int step = static_cast<int>(distance);
    const glm::vec3 dir = glm::normalize(end - start);

    for (int i = 1; i < step; ++i)
    {
        glm::vec3 position = start + (static_cast<float>(i) * dir);

        Chunk* chunk = m_Chunks.GetChunks(position);
        BlockId block = chunk->GetBlockId(position);
        if (block != BlockId::Air)
        {
            hit.Hit = true;
            hit.blockPose = position;
            hit.BlockType = block;
            return;
        }
    }
}
