#include "GeometryInOut.h"

bool GeometryInOut::Import(std::string file, GeometryData& geometryData)
{
	std::fstream stream(file);
	if (!stream)
	{
		std::cout << "File: " << file << " doesn't exist" << std::endl;
		ASSERT(false);
		return false;
	}
	stream.close();

	if (file.size() <= 4)
	{
		std::cout << "File: " << file << " is too short" << std::endl;
		ASSERT(false);
		return false;
	}

	std::string extension = file.substr(file.length() - 4);
	if (extension == ".obj")
	{
		return ImportObj(file, geometryData);
	}
	else
	{
		std::cout << "File type: " << extension << " is not supported" << std::endl;
		ASSERT(false);
		return false;
	}

	return false;
}

bool GeometryInOut::ImportObj(std::string file, GeometryData& geometryData)
{
	std::string name;
	std::vector<glm::vec3> inVerticies;
	std::vector<glm::vec3> inNormals;
	std::vector<glm::vec2> inTextCoords;
	std::vector<std::vector<glm::ivec3>> inFaces; //Note values are one greater than index
	bool isShaded = false;

	std::fstream stream(file);

	//Import all data
	std::string line;
	unsigned int i = -1;
	while (std::getline(stream, line))
	{
		i++;

		//Comment
		if (line == "" || line[0] == '#')
		{
			continue;
		}

		std::vector<std::string> parse;
		size_t pos = 0;
		std::string token = line.substr(0, line.find(' '));
		while ((pos = line.find(' ')) != std::string::npos)
		{
			token = line.substr(0, pos);
			parse.push_back(token);
			line = line.substr(pos + 1);
		}
		parse.push_back(line);

		//Name of ojbect
		if (parse[0] == "o")
		{
			if (parse.size() != 2)
			{
				std::cout << "File: " << file << " not valid on line " << i << std::endl;
				ASSERT(false);
				continue;
			}
			name = parse[1];
		}
		//Imported material
		else if (parse[0] == "mtllib")
		{
			if (parse.size() != 2)
			{
				std::cout << "File: " << file << " not valid on line " << i << std::endl;
				ASSERT(false);
				continue;
			}
			std::cout << "File: " << file << " imported material " << parse[1] << std::endl;
		}
		//Use material
		else if (parse[0] == "usemtl")
		{
			if (parse.size() != 2)
			{
				std::cout << "File: " << file << " not valid on line " << i << std::endl;
				ASSERT(false);
				continue;
			}
			std::cout << "File: " << file << " using material " << parse[1] << std::endl;
		}
		//Verticies
		else if (parse[0] == "v")
		{
			if (parse.size() != 4)
			{
				std::cout << "File: " << file << " not valid on line " << i << std::endl;
				ASSERT(false);
				continue;
			}
			inVerticies.push_back({ stof(parse[1]), stof(parse[2]), stof(parse[3]) });
		}
		//Normals
		else if (parse[0] == "vn")
		{
			if (parse.size() != 4)
			{
				std::cout << "File: " << file << " not valid on line " << i << std::endl;
				ASSERT(false);
				return false;
			}
			inNormals.push_back({ stof(parse[1]), stof(parse[2]), stof(parse[3]) });
		}
		//Texture Coordinates
		else if (parse[0] == "vt")
		{
			if (parse.size() != 3)
			{
				std::cout << "File: " << file << " not valid on line " << i << std::endl;
				ASSERT(false);
				return false;
			}
			inTextCoords.push_back({ stof(parse[1]), stof(parse[2]) });
		}
		//Faces
		else if (parse[0] == "f")
		{
			if (parse.size() < 4)
			{
				std::cout << "File: " << file << " not valid on line " << i << std::endl;
				ASSERT(false);
				return false;
			}

			//**Fix Error Check**
			std::vector<glm::ivec3> face;
			for (unsigned int faceIndex = 1; faceIndex < parse.size(); faceIndex++)
			{
				glm::ivec3 values;
				size_t pos = 0;

				//Subtracts 1 since .obj indexing starts at 1
				values.x = stoi(parse[faceIndex].substr(0, pos = parse[faceIndex].find('/'))) - 1;
				parse[faceIndex] = parse[faceIndex].substr(pos + 1);
				values.y = stoi(parse[faceIndex].substr(0, pos = parse[faceIndex].find('/'))) - 1;
				parse[faceIndex] = parse[faceIndex].substr(pos + 1);
				values.z = stoi(parse[faceIndex]) - 1;

				face.push_back(values);
			}
			inFaces.push_back(face);
		}
		//Smoothed?
		else if (parse[0] == "s")
		{
			if (parse.size() != 2)
			{
				std::cout << "File: " << file << " not valid on line " << i << std::endl;
				ASSERT(false);
				return false;
			}
			isShaded = parse[1] == "1";
		}
		//Not found
		else
		{
			std::cout << "File: " << file << " can't read line " << i << std::endl;
			ASSERT(false);
			return false;
		}
	}

	//Process/Convert data

	//meshVertice and face constructions
	//**Fix: Optimize number of verticies**
	//Doesn't include duplicate verticies
	std::vector<meshVertice> verticies;
	std::vector<glm::ivec3> faces;

	std::map<glm::ivec3, unsigned int, glmCmp> helperMap; //(inVector, outVindex)
	unsigned int verticeIndex = 0;
	for (unsigned int f = 0; f < inFaces.size(); f++)
	{
		std::vector<glm::ivec3>& face = inFaces[f];
		//Verticies
		for (unsigned int v = 0; v < face.size(); v++)
		{
			glm::ivec3& vertice = face[v];
			auto ret = helperMap.emplace(vertice, verticeIndex);
			if (ret.second)
			{
				//Insertion happened
				//**Fix Error Check**
				//Vertice
				verticies.push_back(meshVertice(inVerticies[vertice.x], inNormals[vertice.z], inTextCoords[vertice.y]));
				verticeIndex++;
			}
		}
		//Faces
		unsigned int pivot = helperMap.find(face[0])->second;
		for (unsigned int v = 0; v < face.size() - 2; v++)
		{
			glm::ivec3 triangle(
				pivot,
				helperMap.find(face[v+1])->second,
				helperMap.find(face[v+2])->second);

			faces.push_back(triangle);
		}
	}

	geometryData = GeometryData(name, verticies, faces, isShaded);
	return true;
}