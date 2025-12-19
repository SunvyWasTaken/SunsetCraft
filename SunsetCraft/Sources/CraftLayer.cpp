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
    Chunk* test;
}

CraftLayer::CraftLayer(SunsetEngine::Scene* scene)
    : SunsetEngine::Layer(scene)
{
    test = new Chunk({0, 0, 0});
}

CraftLayer::~CraftLayer()
{
    delete test;
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
    test->Draw();
    if (CraftScene* scene = static_cast<CraftScene*>(GetScene()))
    {
        scene->m_Chunks.Draw(scene);
    }
}

