#pragma once

#include <GL/glew.h>

#include "Debug.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int myRendererId;

	VertexBuffer* myVb;
	VertexBufferLayout* myLayout;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer* vb, VertexBufferLayout* layout);
	void AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;

	inline const VertexBuffer* GetVertexBuffer() const { return myVb; }
	inline const VertexBufferLayout* GetLayout() const { return myLayout; }
};