//
// Created by sunvy on 08/02/2026.
//

#include "GameLayer.h"

#include "../World/CraftScene.h"

GameLayer::GameLayer()
    : SunsetEngine::Layer()
    , m_craftScene(std::make_unique<CraftScene>())
{
}

CraftScene* GameLayer::GetScene() const
{
    return m_craftScene.get();
}

void GameLayer::OnUpdate(float dt)
{
    m_craftScene->Update(dt);
}

void GameLayer::OnDraw()
{
    m_craftScene->Render();
}
