#include "Texture.h"

Texture::Texture(const std::string& path) : 
	myRendererId(0),
	myFilepath(path), 
	myHeight(0),
	myWidth(0),
	myLocalBuffer(nullptr),
	myBpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	myLocalBuffer = stbi_load(path.c_str(), &myWidth, &myHeight, &myBpp, 4);

	GlCall(glGenTextures(1, &myRendererId));
	GlCall(glBindTexture(GL_TEXTURE_2D, myRendererId));

	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, myWidth, myHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, myLocalBuffer));
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (myLocalBuffer)
		stbi_image_free(myLocalBuffer);
}
Texture::~Texture()
{
	GlCall(glDeleteTextures(1, &myRendererId));
}

void Texture::Bind(unsigned int slot) const
{
	GlCall(glActiveTexture(GL_TEXTURE0 + slot));
	GlCall(glBindTexture(GL_TEXTURE_2D, myRendererId));
}
void Texture::Unbind() const
{
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));
}