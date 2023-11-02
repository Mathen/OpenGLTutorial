#pragma once

#include "Fractal.h"

class CubeFractal : public Fractal
{
public:
	CubeFractal(Shader* shader);

	void Divide();
};