//
// Created by sunvy on 15/12/2025.
//

#include "Camera.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"
#include "Math/AABB.h"

#include <glm/gtc/matrix_transform.hpp>

namespace
{
    void UpdateForward(glm::vec3& forward, const float yaw, const float pitch)
    {
        forward.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
        forward.y = glm::sin(glm::radians(pitch));
        forward.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

        forward = glm::normalize(forward);
    }
}

namespace SunsetEngine
{
    bool Frustum::IsVisible(const AABB& box)
    {
        for (auto plane : planes)
        {
            glm::vec3 normal = glm::vec3(plane);
            float distance = plane.w;

            // point le plus loin dans la direction du plan
            glm::vec3 positiveVertex = box.min;

            if (normal.x >= 0) positiveVertex.x = box.max.x;
            if (normal.y >= 0) positiveVertex.y = box.max.y;
            if (normal.z >= 0) positiveVertex.z = box.max.z;

            if (glm::dot(normal, positiveVertex) + distance < 0)
                return false;
        }

        return true;
    }

    Camera::Camera()
        : m_Position(0.f, 0.f, 0.f)
        , m_Forward(0.0f, 0.0f, -1.0f)
        , m_Up(0.0f, 1.0f, 0.0f)
        , m_Yaw(-90.f)
        , m_Pitch(0.f)
        , fov(45.f)
    {
    }

    Camera::~Camera()
    {
    }

    glm::mat4 Camera::GetProjection() const
    {
        const glm::ivec2& src = Application::GetSetting().WindowSize;
        return glm::perspective(glm::radians(fov), static_cast<float>(src.x) / static_cast<float>(src.y), 0.1f, 1000.0f);
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
    }

    glm::vec3 Camera::GetPosition() const
    {
        return m_Position;
    }

    glm::vec3 Camera::GetForward() const
    {
        return m_Forward;
    }

    glm::vec3 Camera::GetUp() const
    {
        return m_Up;
    }

    void Camera::SetForward(const glm::vec3& forward)
    {
        m_Forward = forward;
    }

    void Camera::AddPosition(glm::vec3 position)
    {
        m_Position += position;
    }

    void Camera::AddPitch(float pitch)
    {
        m_Pitch += pitch;
        m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

        UpdateForward(m_Forward, m_Yaw, m_Pitch);
    }

    void Camera::AddYaw(float yaw)
    {
        m_Yaw += yaw;

        UpdateForward(m_Forward, m_Yaw, m_Pitch);
    }

    Frustum Camera::GetFrustum() const
    {
        glm::mat4 vp = GetProjection() * GetViewMatrix();

        Frustum f{};

        f.planes[0] = vp[3] + vp[0]; // left
        f.planes[1] = vp[3] - vp[0]; // right
        f.planes[2] = vp[3] + vp[1]; // bottom
        f.planes[3] = vp[3] - vp[1]; // top
        f.planes[4] = vp[3] + vp[2]; // near
        f.planes[5] = vp[3] - vp[2]; // far

        for (auto & plane : f.planes)
        {
            const float length = glm::length(glm::vec3(plane));
            plane /= length;
        }

        return f;
    }
}
