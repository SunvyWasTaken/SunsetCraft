//
// Created by sunvy on 15/12/2025.
//

#include "Application.h"

#include "ApplicationSetting.h"
#include "Layer.h"
#include "Scene.h"
#include "Render/RenderCommande.h"
#include "Render/Renderer.h"

namespace
{
    SunsetEngine::Renderer* m_Render = nullptr;

    bool IsAppRunning = true;

    SunsetEngine::ApplicationSetting AppSetting;
}

namespace SunsetEngine
{
    Application::Application(const ApplicationSetting& setting)
        : m_LayerStack()
        , m_Scene(nullptr)
    {
        LOG("App Create")
        AppSetting = setting;
        m_Render = new Renderer();
    }

    Application::~Application()
    {
        m_LayerStack.Clear();

        delete m_Render;
        m_Render = nullptr;
    }

    void Application::Run()
    {
        std::chrono::steady_clock::time_point prev = std::chrono::steady_clock::now();

        while (IsAppRunning && m_Render->Valid())
        {
            std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
            std::chrono::duration<float> dt = now - prev;
            prev = now;

            for (const auto& layer : m_LayerStack)
            {
                layer->OnUpdate(dt.count());
            }

            RenderCommande::BeginFrame();
            for (auto layer = m_LayerStack.end(); layer != m_LayerStack.begin(); )
            {
                (*--layer)->OnDraw();
            }
            RenderCommande::EndFrame();
        }
    }

    const ApplicationSetting& Application::GetSetting()
    {
        return AppSetting;
    }

    void Application::ResizeWindow(const glm::ivec2& setting)
    {
        AppSetting.WindowSize = setting;
    }
}
