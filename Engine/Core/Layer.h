//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_LAYER_H
#define SUNSETCRAFT_LAYER_H

namespace SunsetEngine
{
    struct Scene;

    class Layer
    {
    public:
        explicit Layer(Scene* scene);
        virtual ~Layer() = default;

        virtual void OnAttach() = 0;

        virtual void OnUpdate(float dt) = 0;
        virtual void OnDraw() = 0;

    protected:
        Scene* GetScene() const;

    private:
        Scene* m_Scene;
    };
}

#endif //SUNSETCRAFT_LAYER_H