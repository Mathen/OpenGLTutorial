#pragma once

#include <GL/glew.h>

#include "Debug.h"
#include "DeviceMemoryManager.h"

class VertexBuffer
{
private:
	unsigned int myRendererId = 0;
	unsigned int mySizeBytes;

public:
	VertexBuffer(const void* data, unsigned int sizeBytes);
	VertexBuffer(VertexBuffer& vb);
	VertexBuffer& operator=(const VertexBuffer& vb);
	VertexBuffer() : mySizeBytes(0), myRendererId(0) {}
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetRendererId() const { return myRendererId; }

	void* GetData() const;
	inline unsigned int GetSizeBytes() const { return mySizeBytes; };
};