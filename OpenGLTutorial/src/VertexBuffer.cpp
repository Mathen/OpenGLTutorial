#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int sizeBytes)
{
    GlCall(glGenBuffers(1, &myRendererId));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, myRendererId));
    GlCall(glBufferData(GL_ARRAY_BUFFER, sizeBytes, data, GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer()
{
    GlCall(glDeleteBuffers(1, &myRendererId));
}

void VertexBuffer::Bind() const
{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, myRendererId));
}
void VertexBuffer::Unbind() const
{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}