#include "CubeFractal.h"

float Cube::size{ 1.0f };

CubeFractal::CubeFractal(Shader& shader)
{
	myMaxDiv = 5;
	myShader = shader;

	cubes.push_back(Cube(0.0f, 0.0f, 0.0f));
	Cube::size = 1.0f;

	std::vector<float> verticies;
	cubes[0].AddVerticies(verticies);
	VertexBuffer vb((void*)verticies.data(), verticies.size() * 4);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	myVertexArray.SetBuffer(vb, layout);

	std::vector<unsigned int> indexes;
	cubes[0].AddIndexes(indexes, 0);
	myIndexBuffer.SetBuffer(indexes.data(), indexes.size());
}

void CubeFractal::Divide()
{
	if (myMaxDiv <= myDiv)
		return;
	myDiv++;

	Cube::size /= 3.0f;
	std::vector<Cube> newCubes;

	for (unsigned int cube = 0; cube < cubes.size(); cube++)
	{
		const glm::vec3 offsets[] =
		{
			{-1.0f, -1.0f, -1.0f},
			{ 0.0f, -1.0f, -1.0f},
			{ 1.0f, -1.0f, -1.0f},
			{-1.0f, -1.0f,  1.0f},
			{ 0.0f, -1.0f,  1.0f},
			{ 1.0f, -1.0f,  1.0f},
			{ 1.0f, -1.0f,  0.0f},
			{-1.0f, -1.0f,  0.0f},
			{-1.0f,  1.0f, -1.0f},
			{ 0.0f,  1.0f, -1.0f},
			{ 1.0f,  1.0f, -1.0f},
			{-1.0f,  1.0f,  1.0f},
			{ 0.0f,  1.0f,  1.0f},
			{ 1.0f,  1.0f,  1.0f},
			{ 1.0f,  1.0f,  0.0f},
			{-1.0f,  1.0f,  0.0f},
			{-1.0f,  0.0f, -1.0f},
			{-1.0f,  0.0f,  1.0f},
			{ 1.0f,  0.0f, -1.0f},
			{ 1.0f,  0.0f,  1.0f},
		};

		for (unsigned int i = 0; i < 20; i++)
		{
			newCubes.push_back(Cube(cubes[cube].myPosition + offsets[i] * 2.0f * Cube::size));
		}
	}
	cubes = newCubes;

	std::vector<float> verticies;
	std::vector<unsigned int> indexes;
	for (unsigned int i = 0; i < cubes.size(); i++)
	{
		cubes[i].AddVerticies(verticies);
		cubes[i].AddIndexes(indexes, i * 8);
	}

	VertexBuffer vb((void*)verticies.data(), verticies.size() * 4);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	myVertexArray.SetBuffer(vb, layout);

	myIndexBuffer.SetBuffer(indexes.data(), indexes.size());
}