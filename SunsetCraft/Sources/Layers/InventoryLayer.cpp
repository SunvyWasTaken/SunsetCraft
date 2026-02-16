//
// Created by sunvy on 08/02/2026.
//

#include "InventoryLayer.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Slate/HorizontalBox.h"
#include "Slate/Square.h"

namespace
{
    constexpr size_t ToolbarSize = 9;
    std::unique_ptr<SunsetEngine::HorizontalBox> ToolbarBox = nullptr;
}

InventoryLayer::InventoryLayer(CraftScene* scene)
    : _scene(scene)
{
    ToolbarBox = std::make_unique<SunsetEngine::HorizontalBox>();
    ToolbarBox->SetPosition({1280/2, 720});
    ToolbarBox->SetPadding({5, 0});
    ToolbarBox->Reserve(ToolbarSize);
    ToolbarBox->SetAnchor({0, -1});
    for (std::uint8_t i = 0; i < ToolbarSize; ++i)
    {
        std::shared_ptr<SunsetEngine::Slate> Square = std::make_shared<SunsetEngine::Square>(glm::ivec2{0,0}, glm::ivec2{74, 74}, glm::vec4{1.0, 0.3, 0.3, 1.0}, 15.f);
        ToolbarBox->AddChild(Square);
    }
}

InventoryLayer::~InventoryLayer()
{
    ToolbarBox.reset();
}

void InventoryLayer::OnUpdate(float dt)
{
}

void InventoryLayer::OnDraw()
{
    ToolbarBox->Draw();

    int length = 15;
    int width = 5;
    int radius = 2;
    glm::vec4 color{1.0, 0.2, 0.2, 0.5};
    int spacecing = 2;

    glm::ivec2 WinSize = SunsetEngine::Application::GetSetting().WindowSize;

    SunsetEngine::Square crossTop{{WinSize.x / 2, WinSize.y / 2 - spacecing}, {width, length}, color, radius};
    crossTop.SetAnchor({0, -1});
    SunsetEngine::Square crossDown{{WinSize.x / 2, WinSize.y / 2 + spacecing}, {width, length}, color, radius};
    crossDown.SetAnchor({0, 1});
    SunsetEngine::Square crossLeft{{WinSize.x / 2 - spacecing, WinSize.y / 2}, {length, width}, color, radius};
    crossLeft.SetAnchor({-1, 0});
    SunsetEngine::Square crossRight{{WinSize.x / 2 + spacecing, WinSize.y / 2}, {length, width}, color, radius};
    crossRight.SetAnchor({1, 0});

    crossTop.Draw();
    crossDown.Draw();
    crossLeft.Draw();
    crossRight.Draw();
}
