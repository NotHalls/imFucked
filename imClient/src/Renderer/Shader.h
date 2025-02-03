#pragma once
#include "IMF_PCH.h"

#include "ext/matrix_float4x4.hpp"
#include "ext/vector_float3.hpp"
#include "ext/vector_int3.hpp"

class Shader
{
private:
  uint32_t m_shaderProgram;
  std::vector<std::string> m_filePaths;

private:
  std::string readFile(const std::string &filePath);
  void processShader(const std::vector<std::string> &shaderFiles);

  std::string getShaderTypeFromExtension(const std::string &filePath);
  int getUniformLocation(const std::string &name);

public:
  Shader() {}
  Shader(const std::vector<std::string> &shaderFiles);
  ~Shader();

  void Bind();
  void Unbind();

  const std::vector<std::string> &GetFilePaths() const { return m_filePaths; };

  void SetUniformFloat(const std::string &uniformName, float value);
  void SetUniformInt(const std::string &uniformName, int value);

  void SetUniformVec3(const std::string &uniformName, const glm::vec3 &value);
  void SetUniformIVec3(const std::string &uniformName, const glm::ivec3 &value);

  void SetUniformMat4(const std::string &uniformName, const glm::mat4 &value);

  static std::shared_ptr<Shader> CreateShader(
      const std::vector<std::string> &shaderFiles);
};