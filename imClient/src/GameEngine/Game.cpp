#include "IMF_PCH.h"

#include "Game.h"
#include "GlobalValues.h"
#include "Renderer/Renderer.h"

#include "ext/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

// @TEMP
#include <SDL3/SDL_events.h>
#include <glad/glad.h>

GameScene::GameScene()
    : m_Camera({static_cast<float>(GetGame().Width) / GetGame().Height})
{
  m_Shader =
      Shader::CreateShader({"imClient/assets/shaders/2DShader.vertex.glsl",
                            "imClient/assets/shaders/2DShader.fragment.glsl"});
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
    }
    break;
  }

  m_Camera.OnEvent(event);
}
void GameScene::OnResize() { m_Camera.OnResize(); }

void GameScene::OnStart() {}

void GameScene::OnUpdate(float dt)
{
  m_Camera.OnUpdate(dt);

  m_Shader->Bind();
  m_VB->Bind();
  m_VA->Bind();
  m_IB->Bind();
  m_VB->SetBufferLayout({{AttribType::Vec3}, {AttribType::Vec4}});
  m_VA->AddVertexBuffer(m_VB);

  glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x),
                                   glm::vec3(1.0f, 0.0f, 0.0f)) *
                       glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y),
                                   glm::vec3(0.0f, 1.0f, 0.0f)) *
                       glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z),
                                   glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * rotation *
                        glm::scale(glm::mat4(1.0f), m_Scale);
  glm::mat4 pvm = m_Camera.GetCameraMatrices().ViewProjectionMatrix * transform;

  m_Shader->SetUniformMat4("u_PVM", pvm);

  glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
}