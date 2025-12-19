//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_RENDERER_H
#define SUNSETCRAFT_RENDERER_H

namespace SunsetEngine
{
    class Renderer final
    {
    public:
        Renderer();
        ~Renderer();

        bool Valid() const;

        void BeginFrame();

        void EndFrame();

        static void* Get();
    };
}

#endif //SUNSETCRAFT_RENDERER_H