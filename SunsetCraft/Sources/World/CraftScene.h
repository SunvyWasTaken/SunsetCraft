//
// Created by sunvy on 16/12/2025.
//

#ifndef SUNSETCRAFT_CRAFTSCENE_H
#define SUNSETCRAFT_CRAFTSCENE_H

#include "Core/Input.h"
#include "Render/Camera.h"

struct RaycastHit;

struct CraftScene
{
    CraftScene();

    ~CraftScene();

    void Update(float deltaTime);

    void Render() const;

    void LineTrace(RaycastHit& hit, const glm::vec3& start, const glm::vec3& forward, float distance);

private:

    bool PlaceBlock(const SunsetEngine::Event::Action& action);

    SunsetEngine::Camera m_Camera;

    // Toolbar
    std::int8_t currentSelectTool = 1;
};


#endif //SUNSETCRAFT_CRAFTSCENE_H