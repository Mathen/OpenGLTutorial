#pragma once

#include <GL/glew.h>

#include "Debug.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int myRendererId;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void RemoveBuffer(unsigned int rendererId);
	void RemoveBuffer(const VertexBuffer& vb);

	void Bind() const;
	void Unbind() const;
};