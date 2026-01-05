//
// Created by sunvy on 05/01/2026.
//

#include "Render.h"

#include <glad/glad.h>

namespace SunsetEngine
{
    void Render::SetWireframe(bool DrawWireframe)
    {
        if (DrawWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void Render::DrawCube()
    {
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 1);
    }
}
