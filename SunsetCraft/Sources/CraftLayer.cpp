//
// Created by sunvy on 15/12/2025.
//

#include "CraftLayer.h"

#include "Chunk/ChunkManager.h"
#include "World/CraftScene.h"
#include "Render/Camera.h"

namespace
{

}

void CraftLayer::OnAttach(SunsetEngine::Scene* scene)
{
    Layer::OnAttach(scene);
}

void CraftLayer::OnUpdate(float dt)
{
    if (CraftScene* scene = static_cast<CraftScene*>(GetScene()))
    {
        ChunkManager::Update(scene->m_Camera.GetPosition());
    }
}

void CraftLayer::OnDraw()
{
    HUD("CraftLayerDraw");
    if (CraftScene* scene = static_cast<CraftScene*>(GetScene()))
    {
        ChunkManager::Draw(scene);
    }
}

