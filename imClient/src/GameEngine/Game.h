#pragma once
#include "IMF_PCH.h"

#include "GameContext.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

class GameScene : public GameLayer
{
private:
  std::vector<float> m_Vertices = {
      // Positions           // Colors (RGBA)
      // Front face
      -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, // Bottom-left (red)
      0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  // Bottom-right (green)
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,   // Top-right (blue)
      -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f,  // Top-left (yellow)

      // Back face
      -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom-left (magenta)
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  // Bottom-right (cyan)
      0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 1.0f,   // Top-right (gray)
      -0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.0f, 1.0f   // Top-left (orange)
  };

  std::vector<uint32_t> m_Indices = {// Front face
                                     0, 1, 2, 2, 3, 0,
                                     // Back face
                                     4, 5, 6, 6, 7, 4,
                                     // Left face
                                     4, 0, 3, 3, 7, 4,
                                     // Right face
                                     1, 5, 6, 6, 2, 1,
                                     // Top face
                                     3, 2, 6, 6, 7, 3,
                                     // Bottom face
                                     4, 5, 1, 1, 0, 4};

  Ref<VertexBuffer> m_VB;
  Ref<IndexBuffer> m_IB;
  Ref<VertexArray> m_VA;
  Ref<Shader> m_Shader;

  uint32_t m_VBID;
  uint32_t m_IBID;
  uint32_t m_VAID;

public:
  GameScene();
  void OnEvent(const SDL_Event &event) override;
  void OnStart() override;
  void OnUpdate(float dt) override;
};