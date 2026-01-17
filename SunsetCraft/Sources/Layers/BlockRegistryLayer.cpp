//
// Created by sunvy on 17/01/2026.
//

#include "BlockRegistryLayer.h"

#include "Utility/BlockRegistry.h"

BlockRegistryLayer::BlockRegistryLayer(SunsetEngine::Scene *scene)
    : SunsetEngine::Layer(scene)
{
}

BlockRegistryLayer::~BlockRegistryLayer()
{
}

void BlockRegistryLayer::OnAttach()
{
    BlockRegistry::Init("SunsetCraft/Sources/BlockReg.json");
}

void BlockRegistryLayer::OnUpdate(float dt)
{
}

void BlockRegistryLayer::OnDraw()
{
}
