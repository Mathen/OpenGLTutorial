#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int sizeArr) : mySize(sizeArr), myRendererId(0)
{
    GlCall(glGenBuffers(1, &myRendererId));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myRendererId));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeArr * 4, data, GL_STATIC_DRAW));
}
IndexBuffer::IndexBuffer() : mySize(0), myRendererId(0)
{

}
IndexBuffer::~IndexBuffer()
{
    GlCall(glDeleteBuffers(1, &myRendererId));
}

void IndexBuffer::SetBuffer(const unsigned int* data, unsigned int sizeArr)
{
    GlCall(glDeleteBuffers(1, &myRendererId));

    mySize = sizeArr;

    GlCall(glGenBuffers(1, &myRendererId));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myRendererId));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeArr * 4, data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myRendererId));
}
void IndexBuffer::Unbind() const
{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int* IndexBuffer::GetData() const
{
    Bind();
    unsigned int* data = new unsigned int[mySize];
    GlCall(glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, mySize * 4, (void*)data));
    return data;
}