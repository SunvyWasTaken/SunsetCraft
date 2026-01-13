//
// Created by sunvy on 11/01/2026.
//

#ifndef SUNSETCRAFT_SLATE_H
#define SUNSETCRAFT_SLATE_H

namespace SunsetEngine
{
    struct Anchor
    {
        struct Top { int8_t val = 1; };
        struct Center { int8_t val = 0; };
        struct Bottom { int8_t val = -1; };

        using Type = std::variant<Center, Top, Bottom>;
    };

    class Slate
    {
    public:
        Slate();
        virtual ~Slate();

        virtual void Draw() const {};

        glm::ivec2 GetPosition() const;
        void SetPosition(const glm::ivec2& position);

        glm::ivec2 GetSize() const;
        void SetSize(const glm::ivec2& size);

    protected:
        bool bIsDirty;
        glm::ivec2 m_Position;
        glm::ivec2 m_Size;
    };
}


#endif //SUNSETCRAFT_SLATE_H