#pragma once

#include <GL/glew.h>

#include "Debug.h"

class IndexBuffer
{
private:
	unsigned int myRendererId;
	unsigned int mySize;

public:
	IndexBuffer(const unsigned int* data, unsigned int sizeArr);
	IndexBuffer();
	~IndexBuffer();

	void SetBuffer(const unsigned int* data, unsigned int sizeArr);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetSize() const { return mySize; }
	unsigned int* GetData() const;
};