//
// Created by sunvy on 04/01/2026.
//

#ifndef SUNSETCRAFT_DEBUGLAYER_H
#define SUNSETCRAFT_DEBUGLAYER_H

#include "Core/Layer.h"

class DebugLayer : public SunsetEngine::Layer
{
public:
    void OnAttach(SunsetEngine::Scene* scene) override;

    void OnUpdate(float dt) override;
    void OnDraw() override;
    bool OnEvent(SunsetEngine::Event::Type& event) override;
};

#endif //SUNSETCRAFT_DEBUGLAYER_H