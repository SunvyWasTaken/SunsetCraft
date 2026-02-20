//
// Created by sunvy on 17/02/2026.
//

#ifndef SUNSETCRAFT_SKYCUBE_H
#define SUNSETCRAFT_SKYCUBE_H

namespace SunsetEngine
{
    class Drawable;
}

class SkyCube
{
public:
    SkyCube();
    ~SkyCube();
    void Update(const float deltaTime);
    void Draw() const;
private:
    std::unique_ptr<SunsetEngine::Drawable> m_Drawable;
};


#endif //SUNSETCRAFT_SKYCUBE_H