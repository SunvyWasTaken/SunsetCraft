//
// Created by sunvy on 15/12/2025.
//

#include "CraftLayer.h"

#include "Chunk/Chunk.h"
#include "Chunk/ChunkManager.h"
#include "World/CraftScene.h"
#include "Render/Camera.h"
#include "World/RaycastHit.h"

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
        RaycastHit hit;
        scene->LineTrace(hit , scene->m_Camera.GetPosition(), scene->m_Camera.GetPosition() + scene->m_Camera.GetForward() * 10.f);
        if (hit.Hit && hit.BlockType != BlockId::Null)
        {
            HUD("BlockId : {}", static_cast<uint8_t>(hit.BlockType));
        }
    }
}

void CraftLayer::OnDraw()
{
    if (CraftScene* scene = static_cast<CraftScene*>(GetScene()))
    {
        scene->m_Chunks.Draw();
    }
}

