#pragma once

#include <GL/glew.h>

#include "Debug.h"

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

	unsigned int GetSize() const { return mySize; }
};