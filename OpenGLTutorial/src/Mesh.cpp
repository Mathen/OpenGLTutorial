#include "Mesh.h"

Mesh::~Mesh()
{
	delete myIndexBuffer;
	delete myShader;
	delete myVertexArray;
}