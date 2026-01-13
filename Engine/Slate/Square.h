//
// Created by sunvy on 11/01/2026.
//

#ifndef SUNSETCRAFT_SQUARE_H
#define SUNSETCRAFT_SQUARE_H

#include "Slate.h"

namespace SunsetEngine
{
    class Shader;

    class Square : public Slate
    {
    public:

        Square(const glm::ivec2& pos, const glm::ivec2& size, const glm::vec4& color = glm::vec4{1.f}, float roundness = 0.f);

        virtual ~Square();

        void Draw() const override;

    private:

        void Clear();

        void Rebuild();

    protected:
        glm::vec4 m_Color;
        float m_Roundness;
    private:
        std::uint32_t m_VAO;
        std::uint32_t m_VBO;
        std::shared_ptr<Shader> m_Shader;
    };
}

#endif //SUNSETCRAFT_SQUARE_H