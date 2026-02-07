//
// Created by sunvy on 16/12/2025.
//

#ifndef SUNSETCRAFT_CRAFTSCENE_H
#define SUNSETCRAFT_CRAFTSCENE_H

#include "../Chunk/ChunkManager.h"
#include "../TexturesManager.h"
#include "Core/Scene.h"
#include "Render/Camera.h"

struct RaycastHit;

struct CraftScene : public SunsetEngine::Scene
{
    CraftScene();

    ~CraftScene() override;

    void Update(float deltaTime) override;

    void Render() override;

    void LineTrace(RaycastHit& hit, const glm::vec3& start, const glm::vec3& forward, const float distance);

    SunsetEngine::Camera m_Camera;
    TexturesManager m_TexturesManager;

    // Toolbar
    std::int8_t currentSelectTool = 1;
};


#endif //SUNSETCRAFT_CRAFTSCENE_H