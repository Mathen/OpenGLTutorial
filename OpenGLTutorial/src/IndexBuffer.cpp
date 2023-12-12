#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int sizeArr) : mySize(sizeArr), myRendererId(0)
{
    GlCall(glGenBuffers(1, &myRendererId));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myRendererId));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeArr * 4, data, GL_STATIC_DRAW));

    DeviceMemoryManager::GetInstance().AddIndexRef(myRendererId);
}
IndexBuffer::IndexBuffer(const std::vector<glm::ivec3>& data) : mySize(data.size() * 3), myRendererId(0)
{
    GlCall(glGenBuffers(1, &myRendererId));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myRendererId));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * 3 * 4, data.data(), GL_STATIC_DRAW));

    DeviceMemoryManager::GetInstance().AddIndexRef(myRendererId);
}
IndexBuffer::IndexBuffer(IndexBuffer& ib)
{
    DeviceMemoryManager::GetInstance().RemoveIndexRef(myRendererId);

    mySize = ib.mySize;
    myRendererId = ib.myRendererId;

    DeviceMemoryManager::GetInstance().AddIndexRef(myRendererId);
}
IndexBuffer& IndexBuffer::operator=(const IndexBuffer& ib)
{
    DeviceMemoryManager::GetInstance().RemoveIndexRef(myRendererId);

    mySize = ib.mySize;
    myRendererId = ib.myRendererId;

    DeviceMemoryManager::GetInstance().AddIndexRef(myRendererId);

    return *this;
}
IndexBuffer::~IndexBuffer()
{
    DeviceMemoryManager::GetInstance().RemoveIndexRef(myRendererId);
}

void IndexBuffer::SetBuffer(const unsigned int* data, unsigned int sizeArr)
{
    DeviceMemoryManager::GetInstance().RemoveIndexRef(myRendererId);

    mySize = sizeArr;

    GlCall(glGenBuffers(1, &myRendererId));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myRendererId));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeArr * 4, data, GL_STATIC_DRAW));

    DeviceMemoryManager::GetInstance().AddIndexRef(myRendererId);
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