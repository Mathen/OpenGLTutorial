#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int sizeArr) : mySize(sizeArr)
{
    GlCall(glGenBuffers(1, &myRendererId));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myRendererId));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeArr * 4, data, GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer()
{
    GlCall(glDeleteBuffers(1, &myRendererId));
}

void IndexBuffer::Bind() const
{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myRendererId));
}
void IndexBuffer::Unbind() const
{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}