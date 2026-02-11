//
// Created by sunvy on 11/02/2026.
//

#ifndef SUNSETCRAFT_MATERIAL_H
#define SUNSETCRAFT_MATERIAL_H

namespace SunsetEngine
{
    class Textures;
    class Shader;

    class Material
    {
    public:
        Material();
        ~Material();

        void Bind() const;

        std::shared_ptr<Shader> m_Shader;
        std::vector<std::shared_ptr<Textures>> m_Textures;
    };
}

#endif //SUNSETCRAFT_MATERIAL_H