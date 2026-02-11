//
// Created by sunvy on 15/01/2026.
//

#include "Random.h"

namespace
{
    template <typename T>
    T Fade(T t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    template <typename T>
    T Lerp(T a, T b, T t)
    {
        return a + (b - a) * t;
    }

    int hash(int x, int y, const int seed)
    {
        int h = x * 374761393
              + y * 668265263
              + seed * 1442695041;

        h = (h ^ (h >> 13)) * 1274126177;
        return h;
    }

    void Gradient(int ix, int iy, float& gx, float& gy, const int seed)
    {
        int h = hash(ix, iy, seed) & 3;

        switch (h)
        {
            case 0: gx =  1; gy =  0; break;
            case 1: gx = -1; gy =  0; break;
            case 2: gx =  0; gy =  1; break;
            case 3: gx =  0; gy = -1; break;
        }
    }

    float DotGradient(int ix, int iy, float x, float y, const int seed)
    {
        float gx, gy;
        Gradient(ix, iy, gx, gy, seed);

        float dx = x - ix;
        float dy = y - iy;

        return dx * gx + dy * gy;
    }
}

namespace SunsetEngine
{
    template<typename T>
        PerlinNoise<T>::PerlinNoise(int seed, float frequency)
        : Random(seed, frequency)
    {
    }

    template<typename T>
    float PerlinNoise<T>::operator()(const glm::vec<2, T> &vec)
    {
        return operator()(vec.x, vec.y);
    }

    template<typename T>
    float PerlinNoise<T>::operator()(T x, T y)
    {
        float xf = x * m_Frequency;
        float yf = y * m_Frequency;

        int x0 = static_cast<int>(floor(xf));
        int y0 = static_cast<int>(floor(yf));

        int x1 = x0 + 1;
        int y1 = y0 + 1;

        float u = Fade(xf - x0);
        float v = Fade(yf - y0);

        float n00 = DotGradient(x0, y0, xf, yf, m_Seed);
        float n01 = DotGradient(x0, y1, xf, yf, m_Seed);
        float n10 = DotGradient(x1, y0, xf, yf, m_Seed);
        float n11 = DotGradient(x1, y1, xf, yf, m_Seed);

        float ix0 = Lerp(n00, n10, u);
        float iy0 = Lerp(n01, n11, u);

        return Lerp(ix0, iy0, v);
    }

    template struct PerlinNoise<float>;
    template struct PerlinNoise<double>;
    template struct PerlinNoise<int>;
}
