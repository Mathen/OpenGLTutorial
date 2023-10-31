#pragma once

#include <GL/glew.h>

#include "Debug.h"

class VertexBuffer
{
private:
	unsigned int myRendererId = 0;
	unsigned int mySizeBytes;

public:
	VertexBuffer(const void* data, unsigned int sizeBytes);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetRendererId() const { return myRendererId; }

	bool GetData(void* data, unsigned int& sizeBytes) const;
};