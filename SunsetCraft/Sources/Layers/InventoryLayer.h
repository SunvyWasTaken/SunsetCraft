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
    explicit InventoryLayer(CraftScene* scene);
    ~InventoryLayer() override;

    void OnUpdate(float dt) override;
    void OnDraw() override;

private:

    bool OpenInventory(const SunsetEngine::Event::Action& type);
    CraftScene* _scene;
};

#endif //SUNSETCRAFT_INVENTORYLAYER_H