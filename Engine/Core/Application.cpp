//
// Created by sunvy on 15/12/2025.
//

#include "Application.h"

#include "ApplicationSetting.h"
#include "Layer.h"
#include "Render/RenderCommande.h"
#include "Render/Renderer.h"

#include <chrono>

namespace
{
    SunsetEngine::Application* app = nullptr;
    SunsetEngine::ApplicationSetting AppSetting;
    bool IsAppRunning = true;
    SunsetEngine::Renderer* m_Render = nullptr;
}

namespace SunsetEngine
{
    Application::Application(const ApplicationSetting& setting)
        : m_LayerStack()
    {
        Log::Init();
        INITLOG("Engine");
        LOG("Engine", info, "App Create");
        app = this;
        AppSetting = setting;
        m_Render = new Renderer();
        m_Render->BindEvent([this](Event::Type& event){ OnEvent(event); });
    }

    Application::~Application()
    {
        m_LayerStack.Clear();

        delete m_Render;
        m_Render = nullptr;

        app = nullptr;

        LOG("Engine", info, "App Destroy");

        Log::Shutdown();
    }

    void Application::Run()
    {
        std::chrono::steady_clock::time_point prev = std::chrono::steady_clock::now();

        while (IsAppRunning && m_Render->Valid())
        {
            std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
            std::chrono::duration<float> dt = now - prev;
            prev = now;

            PRINTSCREEN("fps : {}", 1.0 / dt.count())

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

    void Application::OnEvent(Event::Type& event)
    {
        for (const auto& layer : m_LayerStack)
        {
            if (layer->OnEvent(event))
                return;
        }
    }

    const ApplicationSetting& Application::GetSetting()
    {
        return AppSetting;
    }

    const Application& Application::GetApplication()
    {
        return *app;
    }

    void Application::ResizeWindow(const glm::ivec2& setting)
    {
        AppSetting.WindowSize = setting;
    }

    void* Application::GetWindow()
    {
        return Renderer::Get();
    }
}
