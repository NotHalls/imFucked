#include "IMF_PCH.h"

#include <glad/glad.h>

#include "glm.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"

std::shared_ptr<Shader> Shader::CreateShader(
    const std::vector<std::string> &shaderFiles)
{
  return std::make_shared<Shader>(shaderFiles);
}

Shader::Shader(const std::vector<std::string> &shaderFiles)
    : m_filePaths(shaderFiles)
{
  processShader(shaderFiles);
}
Shader::~Shader() { glDeleteProgram(m_shaderProgram); }

void Shader::processShader(const std::vector<std::string> &shaderFiles)
{
  m_shaderProgram = glCreateProgram();

  for(const std::string &file : shaderFiles)
  {
    GLenum shaderType;
    if(getShaderTypeFromExtension(file) == ".vertex.glsl")
      shaderType = GL_VERTEX_SHADER;
    else if(getShaderTypeFromExtension(file) == ".fragment.glsl")
      shaderType = GL_FRAGMENT_SHADER;
    else
      throw std::runtime_error(
          "Somethign Went Wrong While Trying To Get Shader Type Shader File");

    uint32_t shader = glCreateShader(shaderType);

    std::string sourceString = readFile(file);
    const char *source = sourceString.c_str();
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, shaderType, &success);
    if(!success)
    {
      const int maxLength = 512;
      char infoLog[maxLength];
      glGetShaderInfoLog(shader, maxLength, nullptr, infoLog);

      glDeleteShader(shader);
      std::cout << "Failed To Compile " << file
                << "\n\tDescription: " << infoLog << std::endl;
    }

    glAttachShader(m_shaderProgram, shader);
  }

  glLinkProgram(m_shaderProgram);
  int success;
  glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
  if(!success)
  {
    const int maxLength = 512;
    char infoLog[maxLength];
    glGetProgramInfoLog(m_shaderProgram, maxLength, nullptr, infoLog);

    glDeleteProgram(m_shaderProgram);
    std::cout << std::string("Failed To Link The Shader Program\n\t")
              << "\n\tDescription: " << infoLog;
  }
}

std::string Shader::readFile(const std::string &filePath)
{
  std::ifstream file(filePath, std::ios::in | std::ios::binary);

  IMF_ASSERT(!(file), "Failed To Open The File: " + filePath);

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

std::string Shader::getShaderTypeFromExtension(const std::string &filePath)
{
  size_t dotPosition = filePath.find_first_of(".");
  std::string extension = filePath.substr(dotPosition);

  if(dotPosition != std::string::npos)
    return extension;

  return "";
}

// BIND AND UNBIND
void Shader::Bind() { glUseProgram(m_shaderProgram); }
void Shader::Unbind() { glUseProgram(0); }

// OPENGL FUNCTIONALITIES //
int Shader::getUniformLocation(const std::string &name)
{
  int location = glGetUniformLocation(m_shaderProgram, name.c_str());
  // @FIXME: the ASSERT is getting called even if the uniform exists
  // ASSERT(location, "Couldn't Find The Uniform '" + name + "'");
  return location;
}

void Shader::SetUniformFloat(const std::string &uniformName, float value)
{
  glUniform1f(getUniformLocation(uniformName), value);
}

void Shader::SetUniformInt(const std::string &uniformName, int value)
{
  glUniform1i(getUniformLocation(uniformName), value);
}

void Shader::SetUniformVec3(const std::string &uniformName,
                            const glm::vec3 &value)
{
  glUniform3f(getUniformLocation(uniformName), value.x, value.y, value.z);
}

void Shader::SetUniformIVec3(const std::string &uniformName,
                             const glm::ivec3 &value)
{
  glUniform3i(getUniformLocation(uniformName), value.x, value.y, value.z);
}

void Shader::SetUniformMat4(const std::string &uniformName,
                            const glm::mat4 &value)
{
  glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE,
                     glm::value_ptr(value));
}