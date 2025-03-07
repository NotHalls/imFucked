#pragma once

#include <cstdint>
#include <memory>
#include <string>

enum class TextureType : short
{
  None = 0,
  Diffuse = 1,
  Roughness = 2,
  Metallic = 3,
  Normal = 4
};
static std::string TextureTypeString(TextureType type)
{
  switch(type)
  {
  case TextureType::Diffuse:
    return "Diffuse";
  case TextureType::Roughness:
    return "Roughness";
  case TextureType::Metallic:
    return "Metallic";
  case TextureType::Normal:
    return "Normal";

  default:
    return "Unknown Texture Type";
  }
  return "Failed To Get TextureTypeString";
}

// @FIXME: this class is giving the GL_ERROR 1280 (INVALID ENUM) Error
class Texture
{
private:
  uint32_t m_ID;
  std::string m_Filepath;

  uint32_t m_Width, m_Height;
  int m_DataColorFormat, m_TextureColorFormat;
  TextureType m_TextureType;

private:
  void Init();
  void InitWithDefaults();

public:
  Texture() = default;
  Texture(int width, int height);
  Texture(const std::string &texPath);
  Texture(const std::string &texPath, TextureType type);
  ~Texture();

  uint32_t Get() { return m_ID; }
  const std::string &GetFilePath() const { return m_Filepath; }
  void SetFilePath(const std::string &filePath) { m_Filepath = filePath; }

  uint32_t GetWidth() { return m_Width; }
  uint32_t GetHeight() { return m_Height; }

  uint32_t GetTextureID() const { return m_ID; }
  void SetTextureID(uint32_t id) { m_ID = id; }

  TextureType GetTextureType() { return m_TextureType; }
  void SetTextureType(TextureType type) { m_TextureType = type; }

  void SetData(void *data, uint32_t size);

  void Bind(uint32_t slot = 0);
  void Unbind(uint32_t slot);

  static Ref<Texture> Create(const std::string &texPath);
  static Ref<Texture> Create(const std::string &texPath, TextureType type);
  // for generating a default 1x1 white texture
  static Ref<Texture> Create(int width, int height);
};