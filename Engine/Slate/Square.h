//
// Created by sunvy on 11/01/2026.
//

#ifndef SUNSETCRAFT_SQUARE_H
#define SUNSETCRAFT_SQUARE_H

namespace SunsetEngine
{
    class Shader;

    class Square
    {
    public:

        Square(const glm::ivec2& pos, const glm::ivec2& size, const glm::vec4& color = glm::vec4{1.f}, float roundness = 0.f);

        virtual ~Square();

        void Draw() const;
    protected:
        glm::ivec2 m_Pos;
        glm::ivec2 m_Size;
        glm::vec4 m_Color;
        float m_Roundness;
    private:
        std::uint32_t m_VAO;
        std::uint32_t m_VBO;
        std::shared_ptr<Shader> m_Shader;
    };
}

#endif //SUNSETCRAFT_SQUARE_H