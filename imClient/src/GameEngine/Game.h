#pragma once
#include "IMF_PCH.h"

#include "GameContext.h"
#include "GameEngine/Camera.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"

class GameScene : public GameLayer
{
private:
  std::vector<float> m_Vertices = {
      // Positions         // Colors (RGBA)        // UVs
      // Front face
      -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
      0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // Bottom-right
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,   // Top-right
      -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // Top-left

      // Back face
      -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Bottom-left
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // Bottom-right
      0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,   // Top-right
      -0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  // Top-left

      // Left face
      -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
      -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // Bottom-right
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,   // Top-right
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // Top-left

      // Right face
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
      0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // Bottom-right
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,   // Top-right
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // Top-left

      // Top face (Fixed UVs)
      -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Top-left
      0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // Top-right
      0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,   // Bottom-right
      -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Bottom-left

      // Bottom face (Fixed UVs)
      -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Top-left
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // Top-right
      0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,   // Bottom-right
      -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f   // Bottom-left
  };
  std::vector<uint32_t> m_Indices = {// Front face
                                     0, 1, 2, 2, 3, 0,
                                     // Back face
                                     4, 5, 6, 6, 7, 4,
                                     // Left face
                                     8, 9, 10, 10, 11, 8,
                                     // Right face
                                     12, 13, 14, 14, 15, 12,
                                     // Top face
                                     16, 17, 18, 18, 19, 16,
                                     // Bottom face
                                     20, 21, 22, 22, 23, 20};

  Ref<VertexBuffer> m_VB;
  Ref<IndexBuffer> m_IB;
  Ref<VertexArray> m_VA;
  Ref<Shader> m_Shader;

  Ref<Texture> m_BoxTexture;

  uint32_t m_VBID;
  uint32_t m_IBID;
  uint32_t m_VAID;

  glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
  glm::vec3 m_Rotation = {0.0f, 0.0f, 0.0f};
  glm::vec3 m_Scale = {1.0f, 1.0f, 1.0f};

  Camera m_Camera;

public:
  GameScene();
  void OnEvent(const SDL_Event &event) override;
  void OnResize() override;
  void OnStart() override;
  void OnUpdate(float dt) override;
};