//
// Created by sunvy on 15/12/2025.
//

#include "CraftLayer.h"

#include "Chunk.h"
#include "ChunkManager.h"
#include "CraftScene.h"
#include "Render/Camera.h"

namespace
{

}

CraftLayer::CraftLayer(SunsetEngine::Scene* scene)
    : SunsetEngine::Layer(scene)
{

}

CraftLayer::~CraftLayer()
{

}

void CraftLayer::OnAttach()
{
}

void CraftLayer::OnUpdate(float dt)
{
    if (CraftScene* scene = static_cast<CraftScene*>(GetScene()))
    {
        scene->m_Chunks.Update(scene->m_Camera.GetPosition());
    }
}

void CraftLayer::OnDraw()
{
    if (CraftScene* scene = static_cast<CraftScene*>(GetScene()))
    {
        scene->m_Chunks.Draw();
    }
}

