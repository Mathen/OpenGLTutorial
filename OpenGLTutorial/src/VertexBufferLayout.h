#pragma once

#include <vector>
#include <GL/glew.h>
#include <stdexcept>

#include "Debug.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int dimention;
	unsigned int normalized;

	static unsigned int GetBytesOfType(unsigned int type)
	{
		if (type == GL_FLOAT)
			return 4;
		if (type == GL_UNSIGNED_INT)
			return 4;
		if (type == GL_UNSIGNED_BYTE)
			return 1;

		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> myElements;
	unsigned int myStride = 0;

public:
	VertexBufferLayout() {}

	template<typename T>
	void Push(unsigned int dimention)
	{
		std::runtime_error("Not supported VertexBufferlayout type");
	}

	template<>
	void Push<float>(unsigned int dimention)
	{
		myElements.push_back({ GL_FLOAT, dimention, GL_FALSE });
		myStride += VertexBufferElement::GetBytesOfType(GL_FLOAT) * dimention;
	}

	template<>
	void Push<unsigned int>(unsigned int dimention)
	{
		myElements.push_back({ GL_UNSIGNED_INT, dimention, GL_FALSE });
		myStride += VertexBufferElement::GetBytesOfType(GL_UNSIGNED_INT) * dimention;
	}

	template<>
	void Push<unsigned char>(unsigned int dimention)
	{
		myElements.push_back({ GL_UNSIGNED_BYTE, dimention, GL_TRUE });
		myStride += VertexBufferElement::GetBytesOfType(GL_UNSIGNED_BYTE) * dimention;
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return myElements; }
	inline const unsigned int GetStride() const { return myStride; }
};