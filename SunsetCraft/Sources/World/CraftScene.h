//
// Created by sunvy on 16/12/2025.
//

#ifndef SUNSETCRAFT_CRAFTSCENE_H
#define SUNSETCRAFT_CRAFTSCENE_H

#include "../Utility/TexturesManager.h"
#include "Render/Camera.h"

struct CraftScene
{
    CraftScene();

    ~CraftScene();

    void Update(float deltaTime);

    void Render() const;

private:

    SunsetEngine::Camera m_Camera;

    // Toolbar
    std::int8_t currentSelectTool = 1;
};


#endif //SUNSETCRAFT_CRAFTSCENE_H