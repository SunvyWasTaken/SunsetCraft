//
// Created by sunvy on 16/12/2025.
//

#ifndef SUNSETCRAFT_CRAFTSCENE_H
#define SUNSETCRAFT_CRAFTSCENE_H

#include "ChunkManager.h"
#include "TexturesManager.h"
#include "Core/Scene.h"
#include "Render/Camera.h"


struct CraftScene : public SunsetEngine::Scene
{
    SunsetEngine::Camera m_Camera;
    ChunkManager m_Chunks;
    TexturesManager m_TexturesManager;
};


#endif //SUNSETCRAFT_CRAFTSCENE_H