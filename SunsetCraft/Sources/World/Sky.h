//
// Created by sunvy on 16/02/2026.
//

#ifndef SUNSETCRAFT_SKY_H
#define SUNSETCRAFT_SKY_H

namespace SunsetEngine
{
    class Textures;
    class Drawable;
}

class Sky
{
public:
    void SetTexture(std::shared_ptr<SunsetEngine::Textures>& textures);
    explicit operator SunsetEngine::Drawable*() const;
private:
    std::unique_ptr<SunsetEngine::Drawable> m_Drawable;
};

#endif //SUNSETCRAFT_SKY_H