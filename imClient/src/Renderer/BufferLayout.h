#pragma once

#include "IMF_PCH.h"

enum class AttribType : int
{
  Float,
  Int,

  Vec2,
  IVec2,
  Vec3,
  IVec3,
  Vec4,
  IVec4,

  Mat2,
  IMat2,
  Mat3,
  IMat3,
  Mat4,
  IMat4
};

static uint32_t GetAttribTypeSize(AttribType type)
{
  switch(type)
  {
  case AttribType::Float:
    return sizeof(float) * 1;
  case AttribType::Int:
    return sizeof(int) * 1;

  case AttribType::Vec2:
    return sizeof(float) * 2;
  case AttribType::Vec3:
    return sizeof(float) * 3;
  case AttribType::Vec4:
    return sizeof(float) * 4;
  case AttribType::IVec2:
    return sizeof(int) * 2;
  case AttribType::IVec3:
    return sizeof(int) * 3;
  case AttribType::IVec4:
    return sizeof(int) * 4;

  case AttribType::Mat2:
    return sizeof(float) * 2 * 2;
  case AttribType::Mat3:
    return sizeof(float) * 3 * 3;
  case AttribType::Mat4:
    return sizeof(float) * 4 * 4;
  case AttribType::IMat2:
    return sizeof(int) * 2 * 2;
  case AttribType::IMat3:
    return sizeof(int) * 3 * 3;
  case AttribType::IMat4:
    return sizeof(int) * 4 * 4;

  default:
    return 0;
  }
};

struct BufferAttrib
{
  AttribType Type;
  bool Normalized;
  uint32_t Offset;
  uint32_t Size;

  uint32_t GetTypeSizeInNumbers(AttribType type)
  {
    switch(type)
    {
    case AttribType::Float:
      return 1;
    case AttribType::Int:
      return 1;

    case AttribType::Vec2:
      return 2;
    case AttribType::Vec3:
      return 3;
    case AttribType::Vec4:
      return 4;
    case AttribType::IVec2:
      return 2;
    case AttribType::IVec3:
      return 3;
    case AttribType::IVec4:
      return 4;

    case AttribType::Mat2:
      return 2 * 2;
    case AttribType::Mat3:
      return 3 * 3;
    case AttribType::Mat4:
      return 4 * 4;
    case AttribType::IMat2:
      return 2 * 2;
    case AttribType::IMat3:
      return 3 * 3;
    case AttribType::IMat4:
      return 4 * 4;

    default:
      return 0;
    }
  }

  BufferAttrib(AttribType type, bool normalized = false)
      : Type(type), Normalized(normalized), Offset(0),
        Size(GetTypeSizeInNumbers(type))
  {
  }
};

struct BufferLayout
{
private:
  std::vector<BufferAttrib> m_bufferAttribs;
  uint32_t m_stride = 0;

private:
  void CalculateAttributes();

public:
  BufferLayout() {}
  BufferLayout(const std::initializer_list<BufferAttrib> &layout);

  uint32_t GetStride() const { return m_stride; }
  const std::vector<BufferAttrib> &GetBufferAttribs() const
  {
    return m_bufferAttribs;
  }
};