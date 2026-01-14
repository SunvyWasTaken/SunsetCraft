//
// Created by sunvy on 13/01/2026.
//

#include "SlateImage.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Render/Camera.h"
#include "Render/Image.h"
#include "Render/Shader.h"

#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>


namespace
{
    std::weak_ptr<SunsetEngine::Shader> shader;

    struct vertice
    {
        glm::vec2 position;
        glm::vec2 uv;
    };

    std::array<vertice, 6> Square{
        vertice{{-1.f,  1.f}, {0, 0}}, // top-left
        vertice{{ 1.f,  1.f}, {1, 0}}, // top-right
        vertice{{ 1.f, -1.f}, {1, 1}}, // bottom-right

        vertice{{ 1.f, -1.f}, {1, 1}},
        vertice{{-1.f, -1.f}, {0, 1}},
        vertice{{-1.f,  1.f}, {0, 0}}
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
    }

    SlateImage::~SlateImage()
    {
        glDeleteTextures(1, &m_Id);
        Clear();
    }

    void SlateImage::LoadImage(const std::string_view &path)
    {
        Image img{path};
        SendTextureToGpu(m_Id, img.width, img.height, img.m_Data);
    }

    void SlateImage::Draw() const
    {
        const_cast<SlateImage*>(this)->Rebuild();
        glm::ivec2 WindowSize = Application::GetSetting().WindowSize;
        m_Shader->Use();
        m_Shader->SetMat4("u_Proj", glm::ortho(0.0f, (float)WindowSize.x, (float)WindowSize.y, 0.0f, -1.0f, 1.0f));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,m_Id);
        const GLint loc = glGetUniformLocation(m_Shader->GetId(), "U_Image");
        glUniform1i(loc, 0);

        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void SlateImage::Rebuild()
    {
        if (!bIsDirty)
            return;

        Clear();

        std::vector<vertice> vertices;
        ComputeVertex(vertices);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertice) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertice), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertice), (void*)offsetof(vertice, uv));

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        bIsDirty = false;
    }

    void SlateImage::ComputeVertex(std::vector<vertice> &vertices)
    {
        vertices.clear();
        vertices.reserve(Square.size());

        for (const auto&[position, uv] : Square)
        {
            const glm::vec2 HalfSize{m_Size.x / 2.f, m_Size.y / 2.f};
            const glm::vec2 width{position.x * HalfSize.x, position.y * HalfSize.y};

            vertices.emplace_back(vertice{{width.x + m_Position.x, width.y + m_Position.y}, uv});
        }
    }

    void SlateImage::Clear()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
}
