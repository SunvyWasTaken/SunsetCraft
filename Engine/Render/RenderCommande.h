//
// Created by sunvy on 05/01/2026.
//

#ifndef SUNSETCRAFT_RENDERCOMMANDE_H
#define SUNSETCRAFT_RENDERCOMMANDE_H

namespace SunsetEngine
{
    class Drawable;

    struct RenderCommande
    {
        static void BeginFrame();
        static void EndFrame();

        static void Submit(const SunsetEngine::Drawable& drawable);
    };
}

#endif //SUNSETCRAFT_RENDERCOMMANDE_H