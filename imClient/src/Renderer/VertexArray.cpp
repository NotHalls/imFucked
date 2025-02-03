#include "IMF_PCH.h"

#include <glad/glad.h>

#include "Buffer.h"
#include "BufferLayout.h"
#include "VertexArray.h"

std::unique_ptr<VertexArray> VertexArray::Create()
{
  return std::make_unique<VertexArray>();
}

VertexArray::VertexArray()
{
  glCreateVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);
}
VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_VAO); }

void VertexArray::Bind() { glBindVertexArray(m_VAO); }
void VertexArray::Unbind() { glBindVertexArray(0); }

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &buffer)
{
  IMF_ASSERT(!(buffer->GetBufferLayout().GetBufferAttribs().size()),
             "You Dont have Any BuffersLayouts Setup In The VertexBuffer")

  glBindVertexArray(m_VAO);
  buffer->Bind();

  const BufferLayout &layout = buffer->GetBufferLayout();

  uint32_t locationIndex = 0;
  for(const BufferAttrib &attrib : layout.GetBufferAttribs())
  {
    glVertexAttribPointer(locationIndex, attrib.Size, GL_FLOAT,
                          attrib.Normalized ? GL_TRUE : GL_FALSE,
                          layout.GetStride() * sizeof(float),
                          (void *)(attrib.Offset * sizeof(float)));
    glEnableVertexAttribArray(locationIndex);

    locationIndex++;
  }
}