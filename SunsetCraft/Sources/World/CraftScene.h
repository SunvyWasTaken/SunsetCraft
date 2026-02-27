//
// Created by sunvy on 16/12/2025.
//

#ifndef SUNSETCRAFT_CRAFTSCENE_H
#define SUNSETCRAFT_CRAFTSCENE_H

#include "Block.h"
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

    bool PlaceBlock(bool destroy);

public:

    // Toolbar
    std::int8_t currentSelectTool = 1;

    std::array<BlockId, 9> m_ToolBar;

private:
    SunsetEngine::Camera m_Camera;

};


#endif //SUNSETCRAFT_CRAFTSCENE_H