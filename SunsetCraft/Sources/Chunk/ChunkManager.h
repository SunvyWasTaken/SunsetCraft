//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_CHUNKMANAGER_H
#define SUNSETCRAFT_CHUNKMANAGER_H

struct BlockType;

class Chunk;
class CraftScene;

class ChunkManager final
{
public:
    static void Init();
    static void Shutdown();

    static void Update(const glm::vec3& position);

    static void SetBlock(const glm::vec3& position, BlockType blockType);

    static BlockType GetBlock(const glm::vec3& position);

    static void Draw(CraftScene* scene);
};

#endif //SUNSETCRAFT_CHUNKMANAGER_H