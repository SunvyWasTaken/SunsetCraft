//
// Created by sunvy on 17/01/2026.
//

#ifndef SUNSETCRAFT_BLOCKREGISTRYLAYER_H
#define SUNSETCRAFT_BLOCKREGISTRYLAYER_H

#include "Core/Layer.h"

class BlockRegistryLayer : public SunsetEngine::Layer
{
public:
    virtual void OnAttach(SunsetEngine::Scene* scene) override;

    virtual void OnUpdate(float dt) override;
    virtual void OnDraw() override;
};

#endif //SUNSETCRAFT_BLOCKREGISTRYLAYER_H