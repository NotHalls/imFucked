#include <iostream>

#include <glad/glad.h>
#include <stb_image.h>

#include "IMFAssert.h"
#include "Memory/Pointer.h"
#include "Texture.h"

Ref<Texture> Texture::Create(const std::string &texPath)
{
  return CreateRef<Texture>(texPath);
}
Ref<Texture> Texture::Create(const std::string &texPath, TextureType type)
{
  return CreateRef<Texture>(texPath, type);
}
Ref<Texture> Texture::Create(int width, int height)
{
  return CreateRef<Texture>(width, height);
}

Texture::Texture(int width, int height) : m_Width(width), m_Height(height)
{
  InitWithDefaults();
}
Texture::Texture(const std::string &texPath)
    : m_Filepath(texPath), m_ID(0), m_Width(0), m_Height(0)
{
  Init();
}
Texture::Texture(const std::string &texPath, TextureType type)
    : m_Filepath(texPath), m_ID(0), m_Width(0), m_Height(0), m_TextureType(type)
{
  Init();
}
Texture::~Texture() { glDeleteTextures(1, &m_ID); }

void Texture::Init()
{
  int width, height, channels;
  stbi_uc *textureData =
      stbi_load(m_Filepath.c_str(), &width, &height, &channels, 0);

  IMF_ASSERT(!textureData, "Failed To Load Image");

  m_Width = width;
  m_Height = height;

  int internalCF, externalCF;

  if(channels == 4)
  {
    internalCF = GL_RGBA8;
    externalCF = GL_RGBA;
  }
  else if(channels == 3)
  {
    internalCF = GL_RGB8;
    externalCF = GL_RGB;
  }

  m_DataColorFormat = internalCF;
  m_TextureColorFormat = externalCF;

  glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
  glTextureStorage2D(m_ID, 1, m_DataColorFormat, m_Width, m_Height);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, m_TextureColorFormat,
                      GL_UNSIGNED_BYTE, textureData);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(textureData);

  glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::InitWithDefaults()
{
  // @TODO: We Have To Make A Default Texture
  // like how we made a Default Model thing
  m_DataColorFormat = GL_RGBA8;
  m_TextureColorFormat = GL_RGBA;

  glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
  glTextureStorage2D(m_ID, 1, m_DataColorFormat, m_Width, m_Height);

  glTexParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::SetData(void *data, uint32_t size)
{
  // remember, when you give the RGBA data, it is reversed (ABGR) not (RGBA)
  // so 0xAABBGGRR not 0xRRGGBBAA

  uint32_t bytesPerPixel = m_TextureColorFormat == GL_RGBA ? 4 : 3;
  IMF_ASSERT(size != m_Width * m_Height * bytesPerPixel,
             "Texture Data Must Be The Size Of The Texture");
  glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, m_TextureColorFormat,
                      GL_UNSIGNED_BYTE, data);
}

void Texture::Bind(uint32_t slot) { glBindTextureUnit(slot, m_ID); }
void Texture::Unbind(uint32_t slot) { glBindTextureUnit(slot, 0); }