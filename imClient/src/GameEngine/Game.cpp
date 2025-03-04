#include "IMF_PCH.h"

#include "Game.h"
#include "Renderer/Renderer.h"

// @TEMP
#include <SDL3/SDL_events.h>
#include <glad/glad.h>

GameScene::GameScene()
{
  m_VA = VertexArray::Create();
  m_IB = IndexBuffer::Create(m_Indices.data(), m_Indices.size());
  m_VB = VertexBuffer::Create(m_Vertices.data(),
                              m_Vertices.size() * sizeof(float));
}

void GameScene::OnEvent(const SDL_Event &event)
{
  switch(event.type)
  {
  case SDL_EVENT_KEY_DOWN:
    switch(event.key.scancode)
    {
    case SDL_SCANCODE_W:
      std::cout << "HEHEH" << std::endl;
      break;
    }
    break;
  }
}

void GameScene::OnStart() {}

void GameScene::OnUpdate(float dt)
{
  Renderer::StartScene();
  m_VB->Bind();
  m_VA->Bind();
  m_IB->Bind();
  m_VB->SetBufferLayout({{AttribType::Vec3}, {AttribType::Vec4}});

  m_VA->AddVertexBuffer(m_VB);
  glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
}