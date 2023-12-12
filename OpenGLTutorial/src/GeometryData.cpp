#include "GeometryData.h"

void GeometryData::Print() const
{
	std::cout << "GeometryData: " << name << std::endl;

	std::cout << "Verticies: " << std::endl;
	for (unsigned int i = 0; i < verticies.size(); i++)
	{
		std::cout << "Vertice " << i << ":\n";
		verticies[i].Print();
	}
	std::cout << std::endl;

	std::cout << "Faces: " << std::endl;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		std::cout << "Face " << i << ": (" << faces[i].x << ", " << faces[i].y << ", " << faces[i].z << ")\n";
	}
}