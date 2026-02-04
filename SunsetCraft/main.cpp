// Sunset inc.

#include "CameraLayer.h"
#include "CraftLayer.h"
#include "DebugLayer.h"
#include "Sources/World/CraftScene.h"
#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Layers/BlockRegistryLayer.h"
#include "Layers/ToolbarLayer.h"

int main()
{
    const SunsetEngine::ApplicationSetting AppSetting{{1280, 720}, "SunsetCraft"};
    SunsetEngine::Application app{AppSetting};
    app.SetScene<CraftScene>();

    app.PushLayer<BlockRegistryLayer>();

    app.PushLayer<ToolbarLayer>();
    app.PushLayer<CraftLayer>();
    app.PushLayer<CameraLayer>();
    //app.PushLayer<DebugLayer>();

    app.Run();
    return 0;
}
