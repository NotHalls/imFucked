#pragma once
#include "IMF_PCH.h"

#include "Shader.h"

class Renderer
{
private:
  struct SceneData
  {
    Ref<Shader> Shader;
  };
  static SceneData *m_SceneData;

public:
  static void Init(const std::vector<std::string> &filePaths);
  static void StartScene();
  static void StopScene();
};