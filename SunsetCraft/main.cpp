// Sunset inc.

#include "Sources/Layers/DebugLayer.h"
#include "Sources/World/CraftScene.h"
#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Layers/GameLayer.h"
#include "Layers/InventoryLayer.h"

int main()
{
    const SunsetEngine::ApplicationSetting AppSetting{{1280, 720}, "SunsetCraft"};
    SunsetEngine::Application app{AppSetting};
    INITLOG("SunsetCraft");

    auto gameLayer = new GameLayer();
    app.AddLayer(gameLayer);
    app.PushLayer<InventoryLayer>(gameLayer->GetScene());
    app.PushLayer<DebugLayer>();

    app.Run();
    return 0;
}
