//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_APPLICATION_H
#define SUNSETCRAFT_APPLICATION_H

#include "Input.h"
#include "LayerStack.h"

namespace SunsetEngine
{
    struct ApplicationSetting;
    class Layer;

    class Application
    {
    public:
        explicit Application(const ApplicationSetting& setting);
        virtual ~Application();

        void Run();

        void OnEvent(Event::Type& event);

        template <typename T>
        requires std::is_base_of_v<SunsetEngine::Layer, T>
        void PushLayer()
        {
            m_LayerStack.PushLayer<T>(m_Scene.get());
        }

        template <typename T>
        requires std::is_base_of_v<SunsetEngine::Scene, T>
        void SetScene()
        {
            m_Scene = std::make_unique<T>();
        }

        static const ApplicationSetting& GetSetting();
        static const Application& GetApplication();
        static void ResizeWindow(const glm::ivec2& setting);

    private:

        SunsetEngine::LayerStack m_LayerStack;

        std::unique_ptr<Scene> m_Scene;
    };
}

#endif //SUNSETCRAFT_APPLICATION_H