//
// Created by sunvy on 16/12/2025.
//

#ifndef SUNSETCRAFT_CRAFTSCENE_H
#define SUNSETCRAFT_CRAFTSCENE_H

#include "../TexturesManager.h"
#include "Render/Camera.h"

struct RaycastHit;

struct CraftScene
{
    CraftScene();

    ~CraftScene();

    void Update(float deltaTime);

    void Render();

    void LineTrace(RaycastHit& hit, const glm::vec3& start, const glm::vec3& forward, const float distance);

    SunsetEngine::Camera m_Camera;
    TexturesManager m_TexturesManager;

    // Toolbar
    std::int8_t currentSelectTool = 1;
};


#endif //SUNSETCRAFT_CRAFTSCENE_H