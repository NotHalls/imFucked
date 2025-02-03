#include "IMF_PCH.h"

#include <glad/glad.h>

#include "Buffer.h"
#include "BufferLayout.h"

// VERTEX BUFFER //
std::shared_ptr<VertexBuffer> VertexBuffer::Create(const float *buffer,
                                                   uint32_t size)
{
  return std::make_shared<VertexBuffer>(buffer, size);
}

VertexBuffer::VertexBuffer(const float *buffer, uint32_t size)
{
  glCreateBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_VBO); }

void VertexBuffer::Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_VBO); }
void VertexBuffer::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

// INDEX BUFFER //
std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t *buffer,
                                                 uint32_t count)
{
  return std::make_shared<IndexBuffer>(buffer, count);
}

IndexBuffer::IndexBuffer(uint32_t *buffer, uint32_t count)
{
  glCreateBuffers(1, &m_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), buffer,
               GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_IBO); }

void IndexBuffer::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO); }
void IndexBuffer::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }