//
// Created by sunvy on 10/01/2026.
//

#include "ToolbarLayer.h"

#include "Slate/Square.h"
#include "World/CraftScene.h"

namespace
{
    constexpr std::uint8_t ToolbarSize = 9;
    std::vector<SunsetEngine::Square> ToolbarSlate;
}

ToolbarLayer::ToolbarLayer(SunsetEngine::Scene* scene)
    : SunsetEngine::Layer(scene)
{
}

ToolbarLayer::~ToolbarLayer()
{
    ToolbarSlate.clear();
}

void ToolbarLayer::OnAttach()
{
    ToolbarSlate.reserve(ToolbarSize);
    const int Size = 25;
    const glm::ivec2 position(640, 580);
    const int HalfToolSize = (ToolbarSize * Size) / 2;
    glm::ivec2 StartPosition{position.x - HalfToolSize, position.y};
    for (std::uint8_t i = 0; i < ToolbarSize; ++i)
    {
        ToolbarSlate.emplace_back(glm::ivec2{StartPosition.x + Size * i, StartPosition.y}, glm::ivec2{Size, Size});
    }
}

void ToolbarLayer::OnUpdate(float dt)
{

}

void ToolbarLayer::OnDraw()
{
    for (const auto& tool : ToolbarSlate)
    {
        tool.Draw();
    }
}

CraftScene* ToolbarLayer::GetCraftScene()
{
    return static_cast<CraftScene*>(GetScene());
}
