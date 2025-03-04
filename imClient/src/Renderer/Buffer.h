#pragma once
#include "IMF_PCH.h"

#include "BufferLayout.h"

class VertexBuffer
{
private:
  uint32_t m_VBO;
  BufferLayout m_bufferLayout;

public:
  VertexBuffer() {}
  VertexBuffer(const float *buffer, uint32_t size);
  ~VertexBuffer();

  void Bind();
  void Unbind();

  void SetBufferLayout(const BufferLayout &layout) { m_bufferLayout = layout; }
  const BufferLayout &GetBufferLayout() const { return m_bufferLayout; }

  static Ref<VertexBuffer> Create(const float *buffer, uint32_t size);
};

class IndexBuffer
{
private:
  uint32_t m_IBO;

public:
  IndexBuffer() {}
  IndexBuffer(uint32_t *buffer, uint32_t count);
  ~IndexBuffer();

  void Bind();
  void Unbind();

  static Ref<IndexBuffer> Create(uint32_t *buffer, uint32_t count);
};