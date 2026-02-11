//
// Created by sunvy on 15/12/2025.
//

#ifndef SUNSETCRAFT_CAMERA_H
#define SUNSETCRAFT_CAMERA_H

namespace SunsetEngine
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

        glm::mat4 GetProjection() const;
        glm::mat4 GetViewMatrix() const;

        glm::vec3 GetPosition() const;
        glm::vec3 GetForward() const;
        glm::vec3 GetUp() const;

        void SetForward(const glm::vec3& forward);

        void AddPosition(glm::vec3 position);

        void AddPitch(float pitch);

        void AddYaw(float yaw);

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Forward;
        glm::vec3 m_Up;

        float m_Yaw, m_Pitch;

        float fov;
    };
}

#endif //SUNSETCRAFT_CAMERA_H
