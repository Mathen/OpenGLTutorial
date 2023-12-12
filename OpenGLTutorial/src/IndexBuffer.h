#pragma once

#include <GL/glew.h>
#include <vector>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Debug.h"
#include "DeviceMemoryManager.h"

class IndexBuffer
{
private:
	unsigned int myRendererId;
	unsigned int mySize;

public:
	IndexBuffer(const unsigned int* data, unsigned int sizeArr);
	IndexBuffer(const std::vector<glm::ivec3>& data);
	IndexBuffer(IndexBuffer& ib);
	IndexBuffer& operator=(const IndexBuffer& ib);
	IndexBuffer() : mySize(0), myRendererId(0) {}
	~IndexBuffer();

	void SetBuffer(const unsigned int* data, unsigned int sizeArr);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetSize() const { return mySize; }
	unsigned int* GetData() const;
};