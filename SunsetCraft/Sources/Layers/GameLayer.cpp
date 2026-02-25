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

bool GameLayer::OnEvent(SunsetEngine::Event::Type& event)
{
    return std::visit(overloads{
        [](SunsetEngine::Event::KeyEvent& e)
        {
            return false;
        },
        [this](SunsetEngine::Event::MouseEvent& e)
        {
            if (e.Scroll != 0)
            {
                m_craftScene->currentSelectTool -= e.Scroll;
                if (m_craftScene->currentSelectTool >= 9)
                    m_craftScene->currentSelectTool = 0;
                else if (m_craftScene->currentSelectTool < 0)
                    m_craftScene->currentSelectTool = 8;

                return true;
            }
            return false;
        }
    }, event);
}
