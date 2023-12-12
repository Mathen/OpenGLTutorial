#pragma once

#include "Debug.h"
#include "Shader.h"
#include "Texture.h"

class Material
{
private:
	Shader myShader;
	Texture myTexture;

public:
	Material() {}
	Material(Shader& sh, Texture& tx) : myShader(sh), myTexture(tx) {}
};