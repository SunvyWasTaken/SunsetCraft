//
// Created by sunvy on 19/12/2025.
//

#ifndef SUNSETCRAFT_TEXTURE_H
#define SUNSETCRAFT_TEXTURE_H


namespace SunsetEngine
{
    class Shader;

    struct Image
    {
    public:
        explicit Image(const std::string_view& path = std::string_view{});
        virtual ~Image();
        void LoadImage(const std::string_view& path);
        void Clear();
        void SetData(unsigned char* data);
        explicit operator bool() const;

        std::string m_ImageName;
        unsigned char* m_Data;
        int width, height, nbrChannels;
    };

    class Texture
    {
    public:

        explicit Texture(const std::shared_ptr<Image>& image);

        virtual ~Texture();

        void Use(const Shader* shader) const;

    private:

        void SenbToGpu();

    private:

        std::shared_ptr<Image> m_image;

        std::uint32_t Id;
    };
}

#endif //SUNSETCRAFT_TEXTURE_H