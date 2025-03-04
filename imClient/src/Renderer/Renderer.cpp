#include "IMF_PCH.h"

#include "Renderer.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

#include "glad/glad.h"

Renderer::SceneData *Renderer::m_SceneData = new Renderer::SceneData();

void Renderer::Init(const std::vector<std::string> &filePaths)
{
  m_SceneData->Shader = Shader::CreateShader(filePaths);
  m_SceneData->Shader->Bind();
}

void Renderer::StartScene() {}

void Renderer::StopScene() {}
