//
// Created by sunvy on 05/01/2026.
//

#ifndef SUNSETCRAFT_RENDERCOMMANDE_H
#define SUNSETCRAFT_RENDERCOMMANDE_H

namespace SunsetEngine
{
    struct RenderCommande
    {
        static void BeginFrame();
        static void EndFrame();

        static void SetWireframe(bool DrawWireframe);
        static void DrawCube();
    };
}

#endif //SUNSETCRAFT_RENDERCOMMANDE_H