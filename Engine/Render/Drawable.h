//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_DRAWABLE_H
#define SUNSETCRAFT_DRAWABLE_H

namespace SunsetEngine
{
    class Drawable final
    {
    public:
        explicit Drawable(const std::vector<std::uint32_t>& indices);
        ~Drawable();

        void Clear() const;

        void Draw() const;

    private:
        std::uint32_t vao, vbo;
        std::size_t vertexCount;
    };
}


#endif //SUNSETCRAFT_DRAWABLE_H