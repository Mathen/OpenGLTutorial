#include "SphereFractal.h"

SphereFractal::SphereFractal(Shader shader)
{
	myMaxDiv = 20;
	myShader = shader;

	glm::vec3 verticies[8] = 
	{
		{-1.0f, -1.0f, -1.0f},
		{-1.0f, -1.0f,  1.0f},
		{-1.0f,  1.0f, -1.0f},
		{-1.0f,  1.0f,  1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f,  1.0f},
		{ 1.0f,  1.0f, -1.0f},
		{ 1.0f,  1.0f,  1.0f},
	};
	unsigned int indexes[] =
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

	VertexBuffer vb((void*)verticies, sizeof(verticies));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	myVertexArray.SetBuffer(vb, layout);

	myIndexBuffer.SetBuffer(indexes, sizeof(indexes) / 4);
}

void SphereFractal::Divide()
{
	if (myMaxDiv <= myDiv)
		return;
	myDiv++;

	const unsigned int length = (myDiv + 1) * 2;
	std::vector<std::vector<std::vector<int>>> grid(length, std::vector<std::vector<int>>(length, std::vector<int>(length, -1)));

	//Solve for a corner of cube-> v:(0,0,0)
	for (unsigned int x = 0; x < length / 2; x++)
	{
		for (unsigned int y = 0; y < length / 2; y++)
		{
			double dx = (length - 1.0f) / 2.0f - x;
			double dy = (length - 1.0f) / 2.0f - y;
			double dz = (length - 1.0f) / 2.0f;

			double target = (length - 1.0) / 2.0;
			double distance = sqrt(dx * dx + dy * dy + dz * dz);
			unsigned int stepsUInt = 0;
			while (distance - target > 0.8)
			{
				dx--;
				dy--;
				dz--;
				distance = sqrt(dx * dx + dy * dy + dz * dz);
				stepsUInt++;
			}

			//Set vertex and rotate to get other 2
			grid[x + stepsUInt][y + stepsUInt][stepsUInt] = -2;
			grid[stepsUInt][x + stepsUInt][y + stepsUInt] = -2;
			grid[y + stepsUInt][stepsUInt][x + stepsUInt] = -2;
		}
	}

	//Mirror other 7 ways to fill in cube
	for (unsigned int x = 0; x < length / 2; x++)
	{
		for (unsigned int y = 0; y < length / 2; y++)
		{
			for (unsigned int z = 0; z < length / 2; z++)
			{
				int value = grid[x][y][z];

				grid[length - 1 - x][y][z] = value;
				grid[length - 1 - x][length - 1 - y][z] = value;
				grid[length - 1 - x][length - 1 - y][length - 1 - z] = value;
				grid[length - 1 - x][y][length - 1 - z] = value;
				grid[x][length - 1 - y][z] = value;
				grid[x][length - 1 - y][length - 1 - z] = value;
				grid[x][y][length - 1 - z] = value;
			}
		}
	}

	//Vertex Array
	int vertexIndex = 0;
	unsigned int maxVerticies = 6 * length * length - 12 * length + 8;
	std::vector<float> verticies(maxVerticies * 3, 0.0f);
	for (unsigned int x = 0; x < length; x++)
	{
		for (unsigned int y = 0; y < length; y++)
		{
			for (unsigned int z = 0; z < length; z++)
			{
				if (grid[x][y][z] == -2)
				{
					grid[x][y][z] = vertexIndex;

					glm::vec3 pos(x, y, z);
					pos -= (length - 1) / 2.0f;
					pos /= (length - 1) / 2.0f;
					verticies[vertexIndex*3+0] = pos.x;
					verticies[vertexIndex*3+1] = pos.y;
					verticies[vertexIndex*3+2] = pos.z;
					/*std::cout << verticies[vertexIndex * 3 + 0] << " " << 
								 verticies[vertexIndex * 3 + 1] << " " << 
								 verticies[vertexIndex * 3 + 2] << " : " << 
								 vertexIndex << std::endl;*/

					vertexIndex++;
				}
			}
		}
	}
	VertexBuffer vb((void*)verticies.data(), vertexIndex * 4 * 3);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	myVertexArray.SetBuffer(vb, layout);

	//Fill indexes
	unsigned int maxTriangles = 2 * 6 * (length - 1) * (length - 1);
	std::vector<unsigned int> indexes(maxTriangles * 3, 0);
	unsigned int indexesIndex = 0;
	//Z plane
	for (unsigned int x = 0; x < length - 1; x++)
	{
		for (unsigned int y = 0; y < length - 1; y++)
		{
			unsigned int z = 0;
			while (z < length && (
				grid[x][y][z] == -1 ||
				grid[x + 1][y][z] == -1 ||
				grid[x][y + 1][z] == -1 ||
				grid[x + 1][y + 1][z] == -1))
			{
				z++;
			}
			if (z != length)
			{
				indexes[indexesIndex++] = grid[x][y][z];
				indexes[indexesIndex++] = grid[x + 1][y][z];
				indexes[indexesIndex++] = grid[x][y + 1][z];
				indexes[indexesIndex++] = grid[x + 1][y + 1][z];
				indexes[indexesIndex++] = grid[x + 1][y][z];
				indexes[indexesIndex++] = grid[x][y + 1][z];

				z = length - 1 - z;
				indexes[indexesIndex++] = grid[x][y][z];
				indexes[indexesIndex++] = grid[x + 1][y][z];
				indexes[indexesIndex++] = grid[x][y + 1][z];
				indexes[indexesIndex++] = grid[x + 1][y + 1][z];
				indexes[indexesIndex++] = grid[x + 1][y][z];
				indexes[indexesIndex++] = grid[x][y + 1][z];
			}
		}
	}
	//Y plane
	for (unsigned int x = 0; x < length - 1; x++)
	{
		for (unsigned int z = 0; z < length - 1; z++)
		{
			unsigned int y = 0;
			while (y < length && (
				grid[x][y][z] == -1 ||
				grid[x + 1][y][z] == -1 ||
				grid[x][y][z + 1] == -1 ||
				grid[x + 1][y][z + 1] == -1))
			{
				y++;
			}
			if (y != length)
			{
				indexes[indexesIndex++] = grid[x][y][z];
				indexes[indexesIndex++] = grid[x + 1][y][z];
				indexes[indexesIndex++] = grid[x][y][z + 1];
				indexes[indexesIndex++] = grid[x + 1][y][z + 1];
				indexes[indexesIndex++] = grid[x + 1][y][z];
				indexes[indexesIndex++] = grid[x][y][z + 1];

				y = length - 1 - y;
				indexes[indexesIndex++] = grid[x][y][z];
				indexes[indexesIndex++] = grid[x + 1][y][z];
				indexes[indexesIndex++] = grid[x][y][z + 1];
				indexes[indexesIndex++] = grid[x + 1][y][z + 1];
				indexes[indexesIndex++] = grid[x + 1][y][z];
				indexes[indexesIndex++] = grid[x][y][z + 1];
			}
		}
	}
	//X plane
	for (unsigned int z = 0; z < length - 1; z++)
	{
		for (unsigned int y = 0; y < length - 1; y++)
		{
			unsigned int x = 0;
			while (x < length && (
				grid[x][y][z] == -1 ||
				grid[x][y][z + 1] == -1 ||
				grid[x][y + 1][z] == -1 ||
				grid[x][y + 1][z + 1] == -1))
			{
				x++;
			}
			if (x != length)
			{
				indexes[indexesIndex++] = grid[x][y][z];
				indexes[indexesIndex++] = grid[x][y][z + 1];
				indexes[indexesIndex++] = grid[x][y + 1][z];
				indexes[indexesIndex++] = grid[x][y + 1][z + 1];
				indexes[indexesIndex++] = grid[x][y + 1][z];
				indexes[indexesIndex++] = grid[x][y][z + 1];

				x = length - 1 - x;
				indexes[indexesIndex++] = grid[x][y][z];
				indexes[indexesIndex++] = grid[x][y][z + 1];
				indexes[indexesIndex++] = grid[x][y + 1][z];
				indexes[indexesIndex++] = grid[x][y + 1][z + 1];
				indexes[indexesIndex++] = grid[x][y + 1][z];
				indexes[indexesIndex++] = grid[x][y][z + 1];
			}
		}
	}
	myIndexBuffer.SetBuffer(indexes.data(), indexesIndex);
}