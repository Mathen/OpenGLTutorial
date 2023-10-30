#pragma once

#include "Renderer.h"

class VertexBuffer
{
private:
	unsigned int myRendererId = 0;

public:
	VertexBuffer(const void* data, unsigned int sizeBytes);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};