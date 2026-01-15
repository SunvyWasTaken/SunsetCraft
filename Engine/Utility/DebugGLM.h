//
// Created by sunvy on 15/01/2026.
//

#ifndef SUNSETCRAFT_DEBUGGLM_H
#define SUNSETCRAFT_DEBUGGLM_H

template <typename T>
struct std::formatter<glm::vec<3, T, glm::defaultp>> : std::formatter<T>
{
    template <typename FormatContext>
    auto format(const glm::vec<3, T, glm::defaultp>& v, FormatContext& ctx) const
    {
        return std::format_to(
            ctx.out(),
            "(x:{}, y:{}, z:{})",
            v.x, v.y, v.z
        );
    }
};

template <typename T>
struct std::formatter<glm::vec<2, T, glm::defaultp>> : std::formatter<T>
{
    template <typename FormatContext>
auto format(const glm::vec<2, T, glm::defaultp>& v, FormatContext& ctx) const
    {
        return std::format_to(
            ctx.out(),
            "(x:{}, y:{})",
            v.x, v.y
        );
    }
};

#endif //SUNSETCRAFT_DEBUGGLM_H