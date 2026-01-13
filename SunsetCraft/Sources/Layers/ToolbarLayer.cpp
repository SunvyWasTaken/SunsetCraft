//
// Created by sunvy on 10/01/2026.
//

#include "ToolbarLayer.h"

#include <glm/ext/quaternion_common.hpp>

#include "Slate/HorizontalBox.h"
#include "Slate/Square.h"
#include "World/CraftScene.h"

namespace
{
    constexpr std::uint8_t ToolbarSize = 9;
    SunsetEngine::HorizontalBox ToolbarSlate;
}

ToolbarLayer::ToolbarLayer(SunsetEngine::Scene* scene)
    : SunsetEngine::Layer(scene)
{
}

ToolbarLayer::~ToolbarLayer()
{
    ToolbarSlate.Clear();
}

void ToolbarLayer::OnAttach()
{
    ToolbarSlate.SetPosition({1280/2, 720-74/2});
    ToolbarSlate.SetPadding({5, 0});
    ToolbarSlate.Reserve(ToolbarSize);
    for (std::uint8_t i = 0; i < ToolbarSize; ++i)
    {
        std::shared_ptr<SunsetEngine::Slate> Square = std::make_shared<SunsetEngine::Square>(glm::ivec2{0,0}, glm::ivec2{74, 74}, glm::vec4{1.0, 0.3, 0.3, 1.0}, 15.f);
        ToolbarSlate.AddChild(Square);
    }
}

void ToolbarLayer::OnUpdate(float dt)
{
}

void ToolbarLayer::OnDraw()
{
    ToolbarSlate.Draw();
}

CraftScene* ToolbarLayer::GetCraftScene()
{
    return static_cast<CraftScene*>(GetScene());
}
