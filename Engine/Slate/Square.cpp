//
// Created by sunvy on 11/01/2026.
//

#include "Square.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Render/Shader.h"

#include <glad/glad.h>
#include <glm/gtc/constants.hpp>

namespace
{
    constexpr int NbrPoints = 32;

    std::weak_ptr<SunsetEngine::Shader> _shader;

    void ComputeRoundedSquare(std::vector<glm::vec2>& points, const glm::ivec2& pos, const glm::ivec2& size, float roundness)
    {
        constexpr float TwoPi = glm::two_pi<float>();

        points.clear();
        points.reserve(NbrPoints);

        constexpr float step = TwoPi / NbrPoints;

        constexpr int Nbr = NbrPoints / 4;

        const std::array<glm::ivec2, 4> offsetPos {
            glm::ivec2{pos.x + size.x / 2, pos.y + size.y / 2},
            {pos.x - size.x / 2, pos.y + size.y / 2},
            {pos.x - size.x / 2, pos.y - size.y / 2},
            {pos.x + size.x / 2, pos.y - size.y / 2}
        };

        int currentSide = 0;
        for (int i = 0; i < NbrPoints; ++i)
        {
            if (i >= currentSide * Nbr)
                ++currentSide;

            const glm::ivec2& currentOffset = offsetPos[currentSide - 1];
            const float xi = roundness * glm::cos(step * i);
            const float yi = roundness * glm::sin(step * i);
            points.emplace_back(currentOffset.x + xi, currentOffset.y + yi);
        }
    }
}

namespace SunsetEngine
{
    Square::Square(const glm::ivec2& pos, const glm::ivec2& size, const glm::vec4& color, float roundness)
        : m_Pos(pos)
        , m_Size(size)
        , m_Color(color)
        , m_Roundness(roundness)
        , m_VAO(0)
        , m_VBO(0)
        , m_Shader(nullptr)
    {
        if (_shader.expired())
        {
            m_Shader =std::make_shared<Shader>("Engine/Shaders/Square.vert", "Engine/Shaders/Square.frag");
            _shader = m_Shader;
        }
        else
            m_Shader = _shader.lock();

        std::vector<glm::vec2> points;
        ComputeRoundedSquare(points, m_Pos, m_Size, m_Roundness);

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * points.size(), points.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glEnableVertexAttribArray(0);
    }

    Square::~Square()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);

        m_VAO = 0;
        m_VBO = 0;
    }

    void Square::Draw() const
    {
        m_Shader->Use();
        m_Shader->SetVec2("u_ScreenSize", Application::GetSetting().WindowSize);

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, NbrPoints);
        glBindVertexArray(0);
    }
}
