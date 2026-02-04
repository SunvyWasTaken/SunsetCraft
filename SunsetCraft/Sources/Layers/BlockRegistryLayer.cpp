//
// Created by sunvy on 17/01/2026.
//

#include "BlockRegistryLayer.h"

#include "Utility/BlockRegistry.h"

void BlockRegistryLayer::OnAttach(SunsetEngine::Scene* scene)
{
    Layer::OnAttach(scene);
    BlockRegistry::Init("SunsetCraft/Sources/BlockReg.json");
}

void BlockRegistryLayer::OnUpdate(float dt)
{
}

void BlockRegistryLayer::OnDraw()
{
}
