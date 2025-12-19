//
// Created by sunvy on 16/12/2025.
//

#ifndef SUNSETCRAFT_CAMERALAYER_H
#define SUNSETCRAFT_CAMERALAYER_H

#include "Core/Layer.h"

namespace SunsetEngine
{
    struct Scene;
}

class CameraLayer : public SunsetEngine::Layer
{
public:
    explicit CameraLayer(SunsetEngine::Scene* scene);
    void OnAttach() override;
    void OnUpdate(float dt) override;
    void OnDraw() override;
};

#endif //SUNSETCRAFT_CAMERALAYER_H