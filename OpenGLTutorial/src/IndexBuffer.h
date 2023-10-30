#pragma once

#include "Renderer.h"

class IndexBuffer
{
private:
	unsigned int myRendererId = 0;
	unsigned int mySize = 0;

public:
	IndexBuffer(const unsigned int* data, unsigned int sizeArr);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
};