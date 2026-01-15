//
// Created by sunvy on 15/01/2026.
//

#ifndef SUNSETCRAFT_RANDOM_H
#define SUNSETCRAFT_RANDOM_H

namespace SunsetEngine
{
    class Random
    {
    public:
        static void InitPerlinNoise(int seed);

        static void InitSimplex(int seed);

        static float PerlinNoise2D(float x, float y);

        static float SimplexNoise3D(float x, float y, float z);
    };
}

#endif //SUNSETCRAFT_RANDOM_H