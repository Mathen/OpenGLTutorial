#include "CubeFractal.h"

CubeFractal::CubeFractal(Shader* shader)
{
	myShader = shader;

	float pos[] =
	{
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
	};
	VertexBuffer* vb = new VertexBuffer(pos, sizeof(pos));
	VertexBufferLayout* layout = new VertexBufferLayout;
	layout->Push<float>(3);
	myVertexArray = new VertexArray;
	myVertexArray->AddBuffer(vb, layout);

	unsigned int indicies[] =
    {
		0, 1, 2,
		1, 2, 3,
		0, 1, 5,
		5, 4, 0,
		1, 3, 7,
		1, 5, 7,
		3, 2, 7,
		7, 6, 2,
		2, 0, 6,
		0, 4, 6,
		5, 4, 6,
		7, 5, 6,
    };
	myIndexBuffer = new IndexBuffer;
	myIndexBuffer->SetBuffer(indicies, sizeof(indicies) / 4);
}

void CubeFractal::Divide()
{
	if (myMaxDiv <= myDiv)
		return;
	myDiv++;

	const VertexBuffer* vb = myVertexArray->GetVertexBuffer();
	float* lastVerticies = (float*)vb->GetData();
	unsigned int lastVbSize = vb->GetSizeBytes() / 4;

	unsigned int* lastIndexes = myIndexBuffer->GetData();
	unsigned int lastIndexSize = myIndexBuffer->GetSize();

	delete myVertexArray;
	delete myIndexBuffer;



	delete lastVerticies;
	delete lastIndexes;
}