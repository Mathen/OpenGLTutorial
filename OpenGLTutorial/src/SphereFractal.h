#pragma once

#include "Fractal.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <math.h> 

class SphereFractal : public Fractal
{
private:
	unsigned int myDiameterVerticies = 1;

public:
	SphereFractal(Shader* shader);

	void Divide();
};