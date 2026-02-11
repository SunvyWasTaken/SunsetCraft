//
// Created by sunvy on 15/01/2026.
//

#ifndef SUNSETCRAFT_RANDOM_H
#define SUNSETCRAFT_RANDOM_H

namespace SunsetEngine
{
    struct Random
    {
        Random(int seed, float frequency) : m_Seed(seed), m_Frequency(frequency) {};

        int m_Seed;
        float m_Frequency;
    };

    template <typename T>
    struct PerlinNoise : public Random
    {
        PerlinNoise(int seed = 0, float frequency = 0);

        float operator()(const glm::vec<2, T>& vec);

        float operator()(T x, T y);
    };

    template <typename T, int Nbr, float freq = 1.f>
    requires std::is_base_of_v<Random, T>
    struct Fbm
    {
        std::array<T, Nbr> Noises;

        explicit Fbm(int seed = 0)
        {
            constexpr float frequency = freq / (Nbr + 1);
            for (int i = 0; i < Nbr; ++i)
            {
                Noises[i] = T(seed, frequency * i);
            }
        }

        template <typename type>
        float operator()(const type& vec)
        {
            return operator()(vec.x, vec.y);
        }

        template <typename type>
        float operator()(const type& x, const type& y)
        {
            float n = 0;
            for (int i = 0; i < Nbr; ++i)
                n += Noises[i](x, y);

            return n;
        }
    };

}

#endif //SUNSETCRAFT_RANDOM_H