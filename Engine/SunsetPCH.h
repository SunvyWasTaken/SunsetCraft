//
// Created by sunvy on 19/12/2025.
//

#ifndef SUNSETCRAFT_SUNSETPCH_H
#define SUNSETCRAFT_SUNSETPCH_H

#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <format>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include  "Log/Logger.h"

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

#endif //SUNSETCRAFT_SUNSETPCH_H