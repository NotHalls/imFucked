#pragma once
#include <iostream>
#include <optional>

#include "Logger/Logger.h"

#include "SDL3/SDL_events.h"
#include "glm.hpp"

class Camera
{
private:
  struct CamMatrices
  {
    glm::mat4 ProjectionMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ViewProjectionMatrix;
  };
  CamMatrices m_CamMatrices;

  struct CamSettings
  {
  public:
    float AspectRatio = 16 / 9;
    float FOV = 90.0f;
    float Sensi = 0.5f;
    float Speed = 5.0f;
    float NearPlane = 0.1f;
    float FarPlane = 100.0f;
  };
  CamSettings m_CamSettings;

  glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
  glm::vec3 m_LookAt = {0.0f, 0.0f, -1.0f};

  float m_Yaw, m_Pitch;
  float m_LastX, m_LastY;
  bool m_FirstMouse;

public:
  Camera(CamSettings settings);

  const CamSettings &GetCameraSettings() const { return m_CamSettings; }
  const CamMatrices &GetCameraMatrices() const { return m_CamMatrices; }

  // settings
  void SetAspectRatio(float aratio)
  {
    m_CamSettings.AspectRatio = aratio;
    RecalculateMatrices();
  }
  void SetFOV(float fov)
  {
    m_CamSettings.FOV = fov;
    RecalculateMatrices();
  }
  void SetSensi(float sensi) { m_CamSettings.Sensi = sensi; }
  void SetSpeed(float speed) { m_CamSettings.Speed = speed; }
  void SetNearPlane(float np)
  {
    m_CamSettings.NearPlane = np;
    RecalculateMatrices();
  }
  void SetFarPlane(float fp)
  {
    m_CamSettings.FarPlane = fp;
    RecalculateMatrices();
  }
  // other properties
  const glm::vec3 GetPosition() const { return m_Position; }
  void SetPosition(const glm::vec3 &pos)
  {
    m_Position = pos;
    RecalculateMatrices();
  }
  const glm::vec3 GetForwardVector() const { return m_LookAt; }

  // Camera Controls
  void OnUpdate(float dt);
  void OnEvent(const SDL_Event &event);
  void OnResize();

private:
  void RecalculateMatrices();
  void UpdateLookAt();
};