#pragma once

#include <GL/glew.h>

#include <string>

#include "stb_image/stb_image.h"

#include "Debug.h"
#include "DeviceMemoryManager.h"

class Texture
{
private:
	unsigned int myRendererId;
	std::string myFilepath;
	unsigned char* myLocalBuffer;

	int myWidth;
	int myHeight;
	int myBpp;

public:
	Texture(const std::string& path);
	Texture(Texture& vb);
	Texture& operator=(const Texture& tx);
	Texture();
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth()  const { return myWidth; }
	inline int GetHeight() const { return myHeight; }
};