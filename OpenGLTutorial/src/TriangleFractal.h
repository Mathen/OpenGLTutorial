#pragma once

#include "Fractal.h"

class TriangleFractal : public Fractal
{
public:
	TriangleFractal(Shader& shader);

	void Divide();
};