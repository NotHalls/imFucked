#include "IMF_PCH.h"

#include "Renderer.h"

// init scene data
Renderer::SceneData *Renderer::m_sceneData = new Renderer::SceneData;

void Renderer::Init(const std::vector<std::string> &filePaths)
{
  m_sceneData->Shader->CreateShader(filePaths);
}
void Renderer::StartScene() { m_sceneData->Shader->Bind(); }
void Renderer::StopScene() {}