#pragma once

#include "Fractal.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

struct Cube
{
	glm::vec3 myPosition;
	bool myFaces[6] = { true }; //0: +x, 1: -x, 2: +y, 3: -y, 4: +z, 5: -z

	static float size;

	Cube(glm::vec3 pos) : myPosition(pos) {}
	Cube(float x, float y, float z) : myPosition({x, y, z}) {}

	void AddVerticies(std::vector<float>& verticies)
	{
		float offsets[] =
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

		for (unsigned int v = 0; v < 24; v += 3)
		{
			verticies.push_back(myPosition.x + offsets[v+0] * size);
			verticies.push_back(myPosition.y + offsets[v+1] * size);
			verticies.push_back(myPosition.z + offsets[v+2] * size);
		}
	}

	void AddIndexes(std::vector<unsigned int>& indexes, unsigned int startVertex)
	{
		unsigned int offsets[] =
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

		for (unsigned int i = 0; i < 36; i++)
		{
			indexes.push_back(startVertex + offsets[i]);
		}
	}
};

class CubeFractal : public Fractal
{
private:
	std::vector<Cube> cubes;

public:
	CubeFractal(Shader* shader);

	void Divide();
};