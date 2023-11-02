#pragma once

#include <GL/glew.h>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexArray.h"
#include "Shader.h"

/*
Mesh contains:
	- Materials (single shader for now)
	- VertexArray
		* Contains layout and verticies
	- IndexBuffer
*/

class Mesh
{
protected:
	IndexBuffer* myIndexBuffer;
	VertexArray* myVertexArray;
	Shader* myShader;

public:
	Mesh(IndexBuffer* ib, Shader* shader, VertexArray* va) : myIndexBuffer(ib), myShader(shader), myVertexArray(va) {}
	~Mesh();

protected:
	Mesh()
	{
		myIndexBuffer = new IndexBuffer();
		myVertexArray = new VertexArray();
		myShader = new Shader();
	}

public:
	const IndexBuffer& GetIndexBuffer() const { return *myIndexBuffer; }
	const Shader& GetShader() const { return *myShader; }
	const VertexArray& GetVertexArray() const { return *myVertexArray; }
};