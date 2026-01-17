//
// Created by sunvy on 15/01/2026.
//

#include "Random.h"

#include <random>
#include <numeric>

#define PERLIN 0
#define SIMPLEX 1

namespace
{
    int* perm()
    {
        static int _perm[512];
        return _perm;
    }

    std::array<bool, 2> bNoiseInit{false, false};

    float fade(float t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    float lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    float grad(int hash, float x, float y)
    {
        switch (hash & 3)
        {
        case 0: return  x + y;
        case 1: return -x + y;
        case 2: return  x - y;
        case 3: return -x - y;
        default: return 0;
        }
    }
}

namespace SunsetEngine
{
    void Random::InitPerlinNoise(int seed)
    {
        std::vector<int> p(256);
        std::iota(p.begin(), p.end(), 0);

        std::mt19937 rng(seed);
        std::shuffle(p.begin(), p.end(), rng);

        for (int i = 0; i < 256; ++i)
        {
            perm()[i] = i;
            perm()[i + 256] = i;
        }

        bNoiseInit[PERLIN] = true;
    }

    void Random::InitSimplex(int seed)
    {
        bNoiseInit[SIMPLEX] = true;
    }


    float Random::PerlinNoise2D(float x, float y)
    {
        if (!bNoiseInit[PERLIN])
        {
            LOG("Perlin Noise not init")
            return 0;
        }

        int X = static_cast<int>(std::floor(x)) & 255;
        int Y = static_cast<int>(std::floor(y)) & 255;

        float xf = x - std::floor(x);
        float yf = y - std::floor(y);

        float u = fade(xf);
        float v = fade(yf);

        int aa = perm()[perm()[X] + Y];
        int ab = perm()[perm()[X] + Y + 1];
        int ba = perm()[perm()[X + 1] + Y];
        int bb = perm()[perm()[X + 1] + Y + 1];

        float x1 = lerp(grad(aa, xf, yf), grad(ba, xf - 1, yf), u);

        float x2 = lerp(grad(ab, xf,     yf - 1),grad(bb, xf - 1, yf - 1),u);

        return lerp(x1, x2, v);
    }

    float Random::SimplexNoise3D(float x, float y, float z)
    {
        // Skewing / unskewing factors for 3D
        static const float F3 = 1.0f / 3.0f;
        static const float G3 = 1.0f / 6.0f;

        // Skew the input space to determine which simplex cell we're in
        float s = (x + y + z) * F3;
        int i = static_cast<int>(std::floor(x + s));
        int j = static_cast<int>(std::floor(y + s));
        int k = static_cast<int>(std::floor(z + s));

        // Unskew the cell origin back to (x,y,z) space
        float t = (i + j + k) * G3;
        float X0 = i - t;
        float Y0 = j - t;
        float Z0 = k - t;
        float x0 = x - X0;
        float y0 = y - Y0;
        float z0 = z - Z0;

        // Determine simplex corner offsets
        int i1, j1, k1; // Offsets for second corner
        int i2, j2, k2; // Offsets for third corner

        // Simplex ordering (x0>=y0>=z0)
        if (x0 >= y0)
        {
            if (y0 >= z0)      { i1=1; j1=0; k1=0;  i2=1; j2=1; k2=0; }
            else if (x0 >= z0) { i1=1; j1=0; k1=0;  i2=1; j2=0; k2=1; }
            else               { i1=0; j1=0; k1=1;  i2=1; j2=0; k2=1; }
        }
        else
        {
            if (y0 < z0)       { i1=0; j1=0; k1=1;  i2=0; j2=1; k2=1; }
            else if (x0 < z0)  { i1=0; j1=1; k1=0;  i2=0; j2=1; k2=1; }
            else               { i1=0; j1=1; k1=0;  i2=1; j2=1; k2=0; }
        }

        // Offsets for the remaining corners
        float x1 = x0 - i1 + G3;
        float y1 = y0 - j1 + G3;
        float z1 = z0 - k1 + G3;

        float x2 = x0 - i2 + 2.0f * G3;
        float y2 = y0 - j2 + 2.0f * G3;
        float z2 = z0 - k2 + 2.0f * G3;

        float x3 = x0 - 1.0f + 3.0f * G3;
        float y3 = y0 - 1.0f + 3.0f * G3;
        float z3 = z0 - 1.0f + 3.0f * G3;

        // Hash the coordinates of the corners
        int ii = i & 255;
        int jj = j & 255;
        int kk = k & 255;

        int gi0 = perm()[ii + perm()[jj + perm()[kk]]] % 12;
        int gi1 = perm()[ii + i1 + perm()[jj + j1 + perm()[kk + k1]]] % 12;
        int gi2 = perm()[ii + i2 + perm()[jj + j2 + perm()[kk + k2]]] % 12;
        int gi3 = perm()[ii + 1 + perm()[jj + 1 + perm()[kk + 1]]] % 12;

        // Gradients for 3D (from classic Simplex Noise)
        static const float grad3[12][3] = {
            {1,1,0}, {-1,1,0}, {1,-1,0}, {-1,-1,0},
            {1,0,1}, {-1,0,1}, {1,0,-1}, {-1,0,-1},
            {0,1,1}, {0,-1,1}, {0,1,-1}, {0,-1,-1}
        };

        // Calculate contributions
        auto contrib = [](float t, const float g[3], float x, float y, float z) -> float {
            if(t < 0) return 0.0f;
            t *= t;
            return t * t * (g[0]*x + g[1]*y + g[2]*z);
        };

        float t0 = 0.6f - x0*x0 - y0*y0 - z0*z0;
        float n0 = contrib(t0, grad3[gi0], x0, y0, z0);

        float t1 = 0.6f - x1*x1 - y1*y1 - z1*z1;
        float n1 = contrib(t1, grad3[gi1], x1, y1, z1);

        float t2 = 0.6f - x2*x2 - y2*y2 - z2*z2;
        float n2 = contrib(t2, grad3[gi2], x2, y2, z2);

        float t3 = 0.6f - x3*x3 - y3*y3 - z3*z3;
        float n3 = contrib(t3, grad3[gi3], x3, y3, z3);

        // Sum and scale to [-1,1]
        return 32.0f * (n0 + n1 + n2 + n3);
    }
}
