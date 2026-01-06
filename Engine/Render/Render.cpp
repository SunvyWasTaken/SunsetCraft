//
// Created by sunvy on 05/01/2026.
//

#include "Render.h"

#include <iostream>
#include <glad/glad.h>

namespace
{
    struct EmptyVAO
    {
        EmptyVAO()
        {
            glCreateVertexArrays(1, &m_EmptyVAO);
        }
        ~EmptyVAO()
        {
            glDeleteVertexArrays(1, &m_EmptyVAO);
        }
        void Use() const
        {
            HUD("VAO BIND {}", m_EmptyVAO)
            glBindVertexArray(m_EmptyVAO);
        }
       uint32_t m_EmptyVAO = 0;
    };

    std::unique_ptr<EmptyVAO> empty_vao = nullptr;
}

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
        if (!empty_vao)
        {
            empty_vao = std::make_unique<EmptyVAO>();
        }
        empty_vao->Use();
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 1);
    }
}
