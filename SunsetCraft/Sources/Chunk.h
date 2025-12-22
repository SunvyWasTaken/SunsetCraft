//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_CHUNK_H
#define SUNSETCRAFT_CHUNK_H

namespace SunsetEngine
{
    class Camera;
    class Shader;
    class Drawable;
    struct AABB;
}

class CraftScene;

class Chunk
{
    constexpr static int m_chunkSize = 32;
public:
    Chunk(const glm::vec3& pos, CraftScene* scene);
    ~Chunk();

    void UseShader(const SunsetEngine::Camera& camera) const;

    void Draw() const;

    void Generate();

    std::vector<SunsetEngine::AABB> GetAABBs(const glm::ivec3& regionMin, const glm::ivec3& regionMax) const;

    static int ChunkSize()
    {
        return m_chunkSize;
    }

    SunsetEngine::Shader* GetShader();

private:
    glm::vec3 position;
    std::array<std::uint8_t, m_chunkSize*m_chunkSize*m_chunkSize> data;

    std::unique_ptr<SunsetEngine::Drawable> m_Drawable;
    std::unique_ptr<SunsetEngine::Shader> m_Shader;
};

#endif //SUNSETCRAFT_CHUNK_H