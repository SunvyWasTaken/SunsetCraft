//
// Created by sunvy on 21/01/2026.
//

#ifndef SUNSETCRAFT_CHUNKUTILITY_H
#define SUNSETCRAFT_CHUNKUTILITY_H

struct triplet_hash
{
    template <typename T>
    std::size_t operator()(const T& t) const
    {
        auto h1 = std::hash<float>{}(t.x);
        auto h2 = std::hash<float>{}(t.y);
        auto h3 = std::hash<float>{}(t.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

#endif //SUNSETCRAFT_CHUNKUTILITY_H