//
// Created by sunvy on 15/12/2025.
//

#include "Camera.h"

#include "Core/Application.h"
#include "Core/ApplicationSetting.h"

#include <glm/gtc/matrix_transform.hpp>

namespace SunsetEngine
{
    Camera::Camera()
        : m_Position(0.f, 10.f, 0.f)
        , m_Forward(0.0f, 0.0f, -1.0f)
        , m_Up(0.0f, 1.0f, 0.0f)
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
}
