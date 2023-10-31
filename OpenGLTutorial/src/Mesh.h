#pragma once

#include "Includes.h"

class Mesh
{
private:
	IndexBuffer  myIndexBuffer;
	VertexBuffer myVerticiesBuffer;
	VertexArray  myVertexArray;

public:
	Mesh(IndexBuffer ib, VertexBuffer vb, VertexArray va) : myIndexBuffer(ib), myVerticiesBuffer(vb), myVertexArray(va) {};
	~Mesh() {};

	const IndexBuffer&  GetIndexBuffer()	 const { return myIndexBuffer; }
	const VertexBuffer& GetVerticiesBuffer() const { return myVerticiesBuffer; }
	const VertexArray&  GetVertexArray()	 const { return myVertexArray; }
};