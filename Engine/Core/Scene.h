//
// Created by sunvy on 16/12/2025.
//

#ifndef SUNSETCRAFT_SCENE_H
#define SUNSETCRAFT_SCENE_H

namespace SunsetEngine
{
    struct Scene
    {
        virtual ~Scene() = default;
        virtual void Update(float deltaTime) = 0;
        virtual void Render() = 0;
    };
}

#endif //SUNSETCRAFT_SCENE_H