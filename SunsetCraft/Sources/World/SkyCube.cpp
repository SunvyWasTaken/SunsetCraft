//
// Created by sunvy on 17/02/2026.
//

#include "SkyCube.h"

#include "Render/Buffers.h"
#include "Render/Drawable.h"
#include "Render/Material.h"
#include "Render/Mesh.h"
#include "Render/RenderCommande.h"
#include "Render/Shader.h"
#include "Render/VertexArray.h"

namespace
{
    struct Vertex
    {
        glm::vec3 position;
    };

    std::vector<Vertex> GenerateSkyDome(float radius, int sectors, int stacks)
    {
        std::vector<Vertex> vertices;
        float PI = M_PI;

        for (int i = 0; i <= stacks; ++i)  // vertical (stack)
        {
            float phi = PI * ((float)i / stacks);

            for (int j = 0; j <= sectors; ++j) // horizontal (sector)
            {
                float theta = 2.0f * PI * ((float)j / sectors); // 0 -> 2PI

                float x = radius * sinf(phi) * cosf(theta);
                float y = radius * cosf(phi);
                float z = radius * sinf(phi) * sinf(theta);

                vertices.push_back(Vertex{ glm::vec3(x, y, z) });
            }
        }

        return vertices;
    }

    std::vector<uint32_t> GenerateSkyDomeIndices(int sectors, int stacks)
    {
        std::vector<uint32_t> indices;

        for (int i = 0; i < stacks; ++i)
        {
            int k1 = i * (sectors + 1);
            int k2 = k1 + sectors + 1;

            for (int j = 0; j < sectors; ++j, ++k1, ++k2)
            {
                indices.push_back(k1);
                indices.push_back(k1 + 1);
                indices.push_back(k2);

                indices.push_back(k1 + 1);
                indices.push_back(k2 + 1);
                indices.push_back(k2);
            }
        }

        return indices;
    }

    constexpr float size = 4000.f;
    constexpr float height = 150.f;

    std::array<glm::vec3, 4> CloudVertices = {
        glm::vec3{-size, height, -size},
        glm::vec3{size, height, -size},
        glm::vec3{size, height, size},
        glm::vec3{-size, height, size}
    };

    std::vector<uint32_t> CloudIndices = {
        0,1,2,
        0,2,3
    };

    std::unique_ptr<SunsetEngine::Drawable> CloudDrawable = nullptr;
}

SkyCube::SkyCube()
    : m_Drawable(std::make_unique<SunsetEngine::Drawable>())
{
    LOG("SunsetCraft", info, "SkyDome generated")
    {
        auto shader = std::make_shared<SunsetEngine::Shader>("SunsetCraft/Shaders/SkyCube.vert", "SunsetCraft/Shaders/SkyCube.frag");
        m_Drawable->m_Material->m_Shader = shader;

        std::vector<Vertex> vertices = GenerateSkyDome(500.f, 64, 32);
        std::vector<uint32_t> indices = GenerateSkyDomeIndices(64, 32);

        auto vbo = std::make_shared<SunsetEngine::VertexBuffer>(vertices.data(), vertices.size(), sizeof(Vertex));
        vbo->SetLayout({SunsetEngine::BufferElement{SunsetEngine::ShaderDataType::Float3, "position"}});

        auto ebo = std::make_shared<SunsetEngine::IndiceBuffer>(indices);

        auto vao = std::make_unique<SunsetEngine::VertexArray>();
        vao->AddVertexBuffer(*vbo);
        vao->AddIndexBuffer(*ebo);

        m_Drawable->m_Mesh = std::make_unique<SunsetEngine::Mesh>(vao);
        m_Drawable->m_Mesh->m_VertexBuffer = vbo;
        m_Drawable->m_Mesh->m_IndiceBuffer = ebo;
    }

    /****************/
    /*Cloud drawable*/
    /****************/

    {
        CloudDrawable = std::make_unique<SunsetEngine::Drawable>();

        auto shader = std::make_shared<SunsetEngine::Shader>("SunsetCraft/Shaders/Cloud.vert", "SunsetCraft/Shaders/Cloud.frag");
        CloudDrawable->m_Material->m_Shader = shader;

        auto vbo = std::make_shared<SunsetEngine::VertexBuffer>(CloudVertices.data(), CloudVertices.size(), sizeof(glm::vec3));
        vbo->SetLayout({SunsetEngine::BufferElement{SunsetEngine::ShaderDataType::Float3, "position"}});

        auto ebo = std::make_shared<SunsetEngine::IndiceBuffer>(CloudIndices);

        auto vao = std::make_unique<SunsetEngine::VertexArray>();
        vao->AddVertexBuffer(*vbo);
        vao->AddIndexBuffer(*ebo);

        CloudDrawable->m_Mesh = std::make_unique<SunsetEngine::Mesh>(vao);
        CloudDrawable->m_Mesh->m_VertexBuffer = vbo;
        CloudDrawable->m_Mesh->m_IndiceBuffer = ebo;
    }


}

SkyCube::~SkyCube()
{
    CloudDrawable.reset();
    LOG("SunsetCraft", info, "SkyDome destroyed")
}

void SkyCube::Draw() const
{
    SunsetEngine::RenderCommande::Submit(*m_Drawable);
    SunsetEngine::RenderCommande::Submit(*CloudDrawable);
}
