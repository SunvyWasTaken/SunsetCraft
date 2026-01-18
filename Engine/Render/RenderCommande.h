//
// Created by sunvy on 05/01/2026.
//

#ifndef SUNSETCRAFT_RENDERCOMMANDE_H
#define SUNSETCRAFT_RENDERCOMMANDE_H
#include "VertexArray.h"

namespace SunsetEngine
{
    struct RenderCommande
    {
    private:
        template <typename T>
        struct FunctorHelper
        {
            static void Submit(const std::shared_ptr<VertexArray<T>>& obj);
            static void SubmitInstance(const std::shared_ptr<VertexArray<T>>& obj, size_t nbrInstance);
        };

    public:
        static void BeginFrame();
        static void EndFrame();

        template <typename T>
        static void Submit(const std::shared_ptr<VertexArray<T>>& obj)
        {
            FunctorHelper<T>::Submit(obj);
        }

        template <typename T>
        static void SubmitInstance(const std::shared_ptr<VertexArray<T>>& obj, size_t nbrInstance)
        {
            FunctorHelper<T>::SubmitInstance(obj, nbrInstance);
        }

        static void SetWireframe(bool DrawWireframe);
        static void DrawCube();
    };
}

#endif //SUNSETCRAFT_RENDERCOMMANDE_H