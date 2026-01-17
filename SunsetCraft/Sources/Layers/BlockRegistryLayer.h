//
// Created by sunvy on 17/01/2026.
//

#ifndef SUNSETCRAFT_BLOCKREGISTRYLAYER_H
#define SUNSETCRAFT_BLOCKREGISTRYLAYER_H

#include "Core/Layer.h"

class BlockRegistryLayer : public SunsetEngine::Layer
{
public:
    explicit BlockRegistryLayer(class SunsetEngine::Scene* scene);
    ~BlockRegistryLayer();

    virtual void OnAttach();

    virtual void OnUpdate(float dt);
    virtual void OnDraw();
};

#endif //SUNSETCRAFT_BLOCKREGISTRYLAYER_H