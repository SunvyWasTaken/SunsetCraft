//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_CHUNKMANAGER_H
#define SUNSETCRAFT_CHUNKMANAGER_H

class Chunk;
class CraftScene;

class ChunkManager final
{
public:
    ChunkManager();
    ~ChunkManager();

    void Update(const glm::vec3& position);

    void Draw() const;

    Chunk* GetChunks(const glm::vec3& position);

private:
    friend class CraftScene;
    CraftScene* m_Scene = nullptr;
};

#endif //SUNSETCRAFT_CHUNKMANAGER_H