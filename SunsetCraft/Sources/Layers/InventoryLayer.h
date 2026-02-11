//
// Created by sunvy on 08/02/2026.
//

#ifndef SUNSETCRAFT_INVENTORYLAYER_H
#define SUNSETCRAFT_INVENTORYLAYER_H

#include "Core/Layer.h"

struct CraftScene;

class InventoryLayer : public SunsetEngine::Layer
{
public:
    InventoryLayer(CraftScene* scene);

    void OnUpdate(float dt) override;
    void OnDraw() override;

private:
    CraftScene* _scene;
};

#endif //SUNSETCRAFT_INVENTORYLAYER_H