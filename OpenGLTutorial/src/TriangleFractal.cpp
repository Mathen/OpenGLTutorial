#include "TriangleFractal.h"

TriangleFractal::TriangleFractal(Shader* shader)
{
	myShader = shader;

	float pos[] =
	{
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 0.0f,  1.0f,
	};
	VertexBuffer* vb = new VertexBuffer(pos, sizeof(pos));
	VertexBufferLayout* layout = new VertexBufferLayout;
	layout->Push<float>(2);
	myVertexArray = new VertexArray;
	myVertexArray->AddBuffer(vb, layout);

	unsigned int indicies[] =
    {
		0, 1, 2,
    };
	myIndexBuffer = new IndexBuffer;
	myIndexBuffer->SetBuffer(indicies, sizeof(indicies) / 4);
}

void TriangleFractal::Divide()
{
	if (myMaxDiv <= myDiv)
		return;
	myDiv++;

	const VertexBuffer* lastVb = myVertexArray->GetVertexBuffer();
	float* lastVerticies = (float*)lastVb->GetData();
	unsigned int lastVbSize = lastVb->GetSizeBytes() / 4;

	unsigned int* lastIndexes = myIndexBuffer->GetData();
	unsigned int lastIndexSize = myIndexBuffer->GetSize();

	delete myVertexArray;
	delete myIndexBuffer;

	std::vector<float> verticies;
	for (unsigned int i = 0; i < lastVbSize; i++)
	{
		verticies.push_back(lastVerticies[i]);
	}
	std::vector<unsigned int> indexes;

	//Fill new Verticies and Indexes
	for (unsigned int triangle = 0; triangle < lastIndexSize; triangle += 3)
	{
		//Coordinates of prvious triange
		float x0 = lastVerticies[lastIndexes[triangle + 0] * 2 + 0];
		float y0 = lastVerticies[lastIndexes[triangle + 0] * 2 + 1];
		float x1 = lastVerticies[lastIndexes[triangle + 1] * 2 + 0];
		float y1 = lastVerticies[lastIndexes[triangle + 1] * 2 + 1];
		float x2 = lastVerticies[lastIndexes[triangle + 2] * 2 + 0];
		float y2 = lastVerticies[lastIndexes[triangle + 2] * 2 + 1];
		
		//Starting index of new verticies
		unsigned int indexOffset = verticies.size() / 2;

		//Add new verticies
		verticies.push_back((x0 + x1) / 2.0f);
		verticies.push_back((y0 + y1) / 2.0f);
		verticies.push_back((x2 + x1) / 2.0f);
		verticies.push_back((y2 + y1) / 2.0f);
		verticies.push_back((x0 + x2) / 2.0f);
		verticies.push_back((y0 + y2) / 2.0f);

		//Construct new triangles
		//Tri1
		indexes.push_back(lastIndexes[triangle + 0]);
		indexes.push_back(indexOffset + 0);
		indexes.push_back(indexOffset + 2);
		//Tri2
		indexes.push_back(lastIndexes[triangle + 1]);
		indexes.push_back(indexOffset + 0);
		indexes.push_back(indexOffset + 1);
		//Tri3
		indexes.push_back(lastIndexes[triangle + 2]);
		indexes.push_back(indexOffset + 1);
		indexes.push_back(indexOffset + 2);
	}

	VertexBuffer* vb = new VertexBuffer(verticies.data(), verticies.size() * 4);
	VertexBufferLayout* layout = new VertexBufferLayout;
	layout->Push<float>(2);
	myVertexArray = new VertexArray;
	myVertexArray->AddBuffer(vb, layout);

	myIndexBuffer = new IndexBuffer;
	myIndexBuffer->SetBuffer(indexes.data(), indexes.size());

	delete lastVerticies;
	delete lastIndexes;
}