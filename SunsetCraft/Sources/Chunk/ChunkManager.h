//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_CHUNKMANAGER_H
#define SUNSETCRAFT_CHUNKMANAGER_H

#include "World/Block.h"

namespace SunsetEngine
{
    class Camera;
}

struct BlockType;

class Chunk;
class CraftScene;

class ChunkManager final
{
public:
    static void Init();
    static void Shutdown();

    static void Update(const glm::vec3& position);

    static void SetBlock(const glm::vec3& position, BlockId blockType);

    static BlockId GetBlock(const glm::vec3& position);

    static void Render(const SunsetEngine::Camera& camera);
};

#endif //SUNSETCRAFT_CHUNKMANAGER_H