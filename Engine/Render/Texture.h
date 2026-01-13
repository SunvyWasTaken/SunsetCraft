//
// Created by sunvy on 19/12/2025.
//

#ifndef SUNSETCRAFT_TEXTURE_H
#define SUNSETCRAFT_TEXTURE_H


namespace SunsetEngine
{
    class Shader;
    struct Image;

    class Textures
    {
    public:
        Textures(std::vector<Image>& images, int width, int height);

        virtual ~Textures();

        void Use(const Shader* shader, const std::string_view& name) const;

        size_t Nbr() const;

        std::uint32_t operator()() const;

        int m_Width, m_Height;

    private:
        std::uint32_t m_Id;
        size_t m_Nbr;
    };
}

#endif //SUNSETCRAFT_TEXTURE_H