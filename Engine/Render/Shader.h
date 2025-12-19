//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_SHADER_H
#define SUNSETCRAFT_SHADER_H

namespace SunsetEngine
{
    class Shader
    {
    public:
        Shader(const std::string_view& vertPath, const std::string_view& fragPath);
        Shader(const char* vertSource, const char* fragSource);
        ~Shader();

        std::uint32_t GetId() const;

        void Use() const;

        void SetVec3(const std::string_view& name, const glm::vec3& value) const;
        void SetMat4(const std::string_view& name, const glm::mat4 &value) const;

    private:
        std::uint32_t id;
    };
}

#endif //SUNSETCRAFT_SHADER_H