//
// Created by sunvy on 13/01/2026.
//

#include "SlateImage.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Render/Image.h"
#include "Render/Shader.h"

#include <glad/glad.h>


namespace
{
    std::weak_ptr<SunsetEngine::Shader> shader;

    struct vertice
    {
        glm::vec2 position;
        glm::vec2 uv;
    };

    std::array<vertice, 6> Square{
        vertice{{250, -250},{1, 0}},
        vertice{{250, 250},{1, 1}},
        vertice{{-250, 250},{0, 1}},
        vertice{{-250, 250},{0, 1}},
        vertice{{-250, -250},{0, 0}},
        vertice{{250, -250},{1, 0}}
    };

    void SendTextureToGpu(std::uint32_t& id, const int width, const int height, void* data = nullptr)
    {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
}

namespace SunsetEngine
{
    SlateImage::SlateImage()
        : m_Shader(nullptr)
        , VAO(0)
        , VBO(0)
        , m_Id(0)
    {
        if (shader.expired())
        {
            m_Shader = std::make_shared<Shader>("Engine/Shaders/SlateImage.vert", "Engine/Shaders/SlateImage.frag");
            shader = m_Shader;
        }

        m_Shader = shader.lock();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertice) * Square.size(), Square.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribIPointer(0, 2, GL_UNSIGNED_INT, sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribIPointer(1, 2, GL_UNSIGNED_INT, sizeof(float), (void*)offsetof(vertice, uv));

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    SlateImage::~SlateImage()
    {
        glDeleteTextures(1, &m_Id);
    }

    void SlateImage::LoadImage(const std::string_view &path)
    {
        Image img{path};
        SendTextureToGpu(m_Id, img.width, img.height, img.m_Data);
    }

    void SlateImage::Draw() const
    {
        m_Shader->Use();
        m_Shader->SetVec2("u_ScreenSize", Application::GetSetting().WindowSize);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,m_Id);
        const GLint loc = glGetUniformLocation(m_Shader->GetId(), "image");
        glUniform1i(loc, 0);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, Square.size());

        glBindVertexArray(0);
    }
}
