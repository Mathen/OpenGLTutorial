#pragma once

#include "VertexBuffer.h";
#include "VertexBufferLayout.h"
#include <stdio.h>

class VertexArray
{
private:
	unsigned int myRendererId;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};