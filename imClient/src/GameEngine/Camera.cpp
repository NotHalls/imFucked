#include "IMF_PCH.h"

#include "Camera.h"
#include "GlobalValues.h"

#include "SDL3/SDL_keyboard.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"

Camera::Camera(CamSettings camSettings) : m_CamSettings(camSettings)
{
  RecalculateMatrices();
  m_Yaw = m_Pitch = 0.0f;
  m_LastX = (float)GetGame().Width;
  m_LastY = (float)GetGame().Height;
  m_FirstMouse = true;
}

void Camera::UpdateLookAt()
{
  glm::vec3 front;
  front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
  front.y = sin(glm::radians(m_Pitch));
  front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

  m_LookAt = glm::normalize(front);
}
void Camera::RecalculateMatrices()
{
  UpdateLookAt();
  m_CamMatrices.ViewMatrix = glm::lookAt(m_Position, m_Position + m_LookAt,
                                         glm::vec3(0.0f, 1.0f, 0.0f));
  m_CamMatrices.ProjectionMatrix = glm::perspective(
      glm::radians(m_CamSettings.FOV), m_CamSettings.AspectRatio,
      m_CamSettings.NearPlane, m_CamSettings.FarPlane);

  m_CamMatrices.ViewProjectionMatrix =
      m_CamMatrices.ProjectionMatrix * m_CamMatrices.ViewMatrix;
}

void Camera::OnEvent(const SDL_Event &event)
{
  if(event.type == SDL_EVENT_MOUSE_MOTION)
  {
    float xOffset = event.motion.xrel * m_CamSettings.Sensi;
    float yOffset = event.motion.yrel * m_CamSettings.Sensi;

    m_Yaw += xOffset;
    m_Pitch -= yOffset;

    // Clamp pitch to avoid flipping the camera
    if(m_Pitch > 89.0f)
      m_Pitch = 89.0f;
    if(m_Pitch < -89.0f)
      m_Pitch = -89.0f;

    UpdateLookAt();
    RecalculateMatrices();
  }
}
void Camera::OnResize()
{
  m_CamSettings.AspectRatio = (float)GetGame().Width / (float)GetGame().Height;
  RecalculateMatrices();
}

void Camera::OnUpdate(float dt)
{
  // @TODO: an input system would be nice
  const bool *keyboardState = SDL_GetKeyboardState(nullptr);
  glm::vec3 moveDirection = {0.0f, 0.0f, 0.0f};

  if(keyboardState[SDL_SCANCODE_W])
  {
    moveDirection += m_LookAt; // Move forward
  }
  if(keyboardState[SDL_SCANCODE_S])
  {
    moveDirection -= m_LookAt; // Move backward
  }
  if(keyboardState[SDL_SCANCODE_A])
  {
    moveDirection -= glm::normalize(
        glm::cross(m_LookAt, glm::vec3(0.0f, 1.0f, 0.0f))); // Move left
  }
  if(keyboardState[SDL_SCANCODE_D])
  {
    moveDirection += glm::normalize(
        glm::cross(m_LookAt, glm::vec3(0.0f, 1.0f, 0.0f))); // Move right
  }

  if(glm::length(moveDirection) > 0.0f)
  {
    moveDirection = glm::normalize(moveDirection) * m_CamSettings.Speed * dt;
    SetPosition(m_Position + moveDirection);
  }
}
