#pragma once

#include <vector>

#include "Mesh.h"

class Fractal : public Mesh
{
protected:
	unsigned int myMaxDiv = 5;
	unsigned int myDiv = 0;

public:
	virtual void Divide() = 0;

	void GetVerticies(std::vector<float>& verticies);
	void GetIndicies(std::vector<unsigned int>& indicies);

	void SetVerticies(std::vector<float>& verticies);
	void SetIndicies(std::vector<unsigned int>& indicies);
};