#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "GL/glew.h"

//vertice struct
struct meshVertice
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoord;

	meshVertice(glm::vec3 p = {0, 0, 0}, glm::vec3 n = { 0, 0, 0 }, glm::vec2 tc = { 0, 0 })
	{
		position = p;
		normal = n;
		textCoord = tc;
	}

	void Print() const
	{
		std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
		std::cout << "Normal: (" << normal.x << ", " << normal.y << ", " << normal.z << ")\n";
		std::cout << "Texture Coordinate: (" << textCoord.x << ", " << textCoord.y << ")\n\n";
	}
};

//Stores a single objects geometry data
class GeometryData
{
private:
	std::string name;
	std::vector<meshVertice> verticies;
	std::vector<glm::ivec3> faces; //Only saves triangles
	bool isShaded = false; //Ignore this feature for now

	//GLenum renderType; //Assume only triangles are bing rendered

public:
	GeometryData(
		std::string& n,
		std::vector<meshVertice>& v,
		std::vector<glm::ivec3>& f,
		bool s)
		: name(n), verticies(v), faces(f), isShaded(s) {}
	GeometryData() {}

	const std::string& GetName() const { return name; }
	const std::vector<meshVertice>& GetVerticies() const { return verticies; }
	const std::vector<glm::ivec3>& GetFaces() const { return faces; }
	const bool GetShaded() const { return isShaded; }

	void Print() const;
};