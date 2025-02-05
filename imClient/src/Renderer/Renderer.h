#pragma once
#include "IMF_PCH.h"

#include "Shader.h"

class Renderer
{
private:
  struct SceneData
  {
    std::shared_ptr<Shader> Shader;
  };
  static SceneData *m_sceneData;

public:
  static void Init(const std::vector<std::string> &filePaths);
  static void StartScene();
  static void StopScene();
};