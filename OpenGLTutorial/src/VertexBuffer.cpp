#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int sizeBytes) : mySizeBytes(sizeBytes)
{
    GlCall(glGenBuffers(1, &myRendererId));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, myRendererId));
    GlCall(glBufferData(GL_ARRAY_BUFFER, sizeBytes, data, GL_STATIC_DRAW));

    DeviceMemoryManager::GetInstance().AddVertexBuffRef(myRendererId);
}
VertexBuffer::VertexBuffer(VertexBuffer& vb)
{
    DeviceMemoryManager::GetInstance().RemoveVertexBuffRef(myRendererId);

    myRendererId = vb.myRendererId;
    mySizeBytes = vb.mySizeBytes;

    DeviceMemoryManager::GetInstance().AddVertexBuffRef(myRendererId);
}
VertexBuffer& VertexBuffer::operator=(const VertexBuffer& vb)
{
    DeviceMemoryManager::GetInstance().RemoveVertexBuffRef(myRendererId);

    myRendererId = vb.myRendererId;
    mySizeBytes = vb.mySizeBytes;

    DeviceMemoryManager::GetInstance().AddVertexBuffRef(myRendererId);
    return *this;
}
VertexBuffer::~VertexBuffer()
{
    DeviceMemoryManager::GetInstance().RemoveVertexBuffRef(myRendererId);
}

void VertexBuffer::Bind() const
{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, myRendererId));
}
void VertexBuffer::Unbind() const
{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void* VertexBuffer::GetData() const
{
    Bind();
    void* data = new unsigned char[mySizeBytes];
    GlCall(glGetBufferSubData(GL_ARRAY_BUFFER, 0, mySizeBytes, (void*)data));
    return data;
}