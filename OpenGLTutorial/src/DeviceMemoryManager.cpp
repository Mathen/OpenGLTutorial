#include "DeviceMemoryManager.h"

DeviceMemoryManager* DeviceMemoryManager::instance = nullptr;

DeviceMemoryManager::DeviceMemoryManager()
{
	if (instance == nullptr)
	{
		instance = this;
	}
	else
	{
		std::cout << "Error: Can only have one instance of DeviceMemoryManager" << std::endl;
		ASSERT(true);
	}
}
DeviceMemoryManager::~DeviceMemoryManager()
{
	std::cout << "Destructor" << std::endl;

	for (auto it = bufferRefCount.begin(); it != bufferRefCount.end(); ++it)
	{
		if (it->second > 0)
		{
			std::cout << "Removing Buffer Ref " << (it->first) << std::endl;
			GlCall(glDeleteBuffers(1, &(it->first)));
		}
	}
	for (auto it = vertexArrRefCount.begin(); it != vertexArrRefCount.end(); ++it)
	{
		if (it->second > 0)
		{
			std::cout << "Removing Vertex Array Ref " << (it->first) << std::endl;
			GlCall(glDeleteVertexArrays(1, &(it->first)));
		}
	}
	for (auto it = shaderRefCount.begin(); it != shaderRefCount.end(); ++it)
	{
		if (it->second > 0)
		{
			std::cout << "Removing Shader Ref " << (it->first) << std::endl;
			GlCall(glDeleteProgram((it->first)));
		}
	}
	for (auto it = textureRefCount.begin(); it != textureRefCount.end(); ++it)
	{
		if (it->second > 0)
		{
			std::cout << "Removing Texture Ref " << (it->first) << std::endl;
			GlCall(glDeleteTextures(1, &(it->first)));
		}
	}
}

void DeviceMemoryManager::AddVertexBuffRef(unsigned int rendererId)
{
	std::cout << "Adding Buffer Ref (v) " << rendererId << std::endl;
	bufferRefCount[rendererId]++;
}
void DeviceMemoryManager::AddVertexArrRef(unsigned int rendererId)
{
	std::cout << "Adding Vertex Array Ref " << rendererId << std::endl;
	vertexArrRefCount[rendererId]++;
}
void DeviceMemoryManager::AddIndexRef(unsigned int rendererId)
{
	std::cout << "Adding Buffer Ref (i) " << rendererId << std::endl;
	bufferRefCount[rendererId]++;
}
void DeviceMemoryManager::AddShaderRef(unsigned int rendererId)
{
	std::cout << "Adding Shader Ref " << rendererId << std::endl;
	shaderRefCount[rendererId]++;
}
void DeviceMemoryManager::AddTextureRef(unsigned int rendererId)
{
	std::cout << "Adding Texture Ref " << rendererId << std::endl;
	textureRefCount[rendererId]++;
}

void DeviceMemoryManager::RemoveVertexBuffRef(unsigned int rendererId)
{
	std::cout << "Removing Buffer Ref (v) " << rendererId << std::endl;
	unsigned int& count = bufferRefCount[rendererId];
	if (count == 1)
	{
		std::cout << "\tDelete Buffer Ref (v) " << rendererId << std::endl;
		GlCall(glDeleteBuffers(1, &rendererId));
	}
	count--;
}
void DeviceMemoryManager::RemoveVertexArrRef(unsigned int rendererId)
{
	std::cout << "Removing Vertex Array Ref " << rendererId << std::endl;
	unsigned int& count = vertexArrRefCount[rendererId];
	if (count == 1)
	{	
		std::cout << "\tDelete Vertex Array Ref " << rendererId << std::endl;
		GlCall(glDeleteVertexArrays(1, &rendererId));
	}
	count--;
}
void DeviceMemoryManager::RemoveIndexRef(unsigned int rendererId)
{
	std::cout << "Removing Buffer Ref (i) " << rendererId << std::endl;
	unsigned int& count = bufferRefCount[rendererId];
	if (count == 1)
	{
		std::cout << "\tDelete Buffer Ref (i) " << rendererId << std::endl;
		GlCall(glDeleteBuffers(1, &rendererId));
	}
	count--;
}
void DeviceMemoryManager::RemoveShaderRef(unsigned int rendererId)
{
	std::cout << "Removing Shader Ref " << rendererId << std::endl;
	unsigned int& count = shaderRefCount[rendererId];
	if (count == 1)
	{
		std::cout << "\tDelete Shader Ref " << rendererId << std::endl;
		GlCall(glDeleteProgram(rendererId));
	}
	count--;
}
void DeviceMemoryManager::RemoveTextureRef(unsigned int rendererId)
{
	std::cout << "Removing Texture Ref " << rendererId << std::endl;
	unsigned int& count = textureRefCount[rendererId];
	if (count == 1)
	{
		std::cout << "\tDelete Texture Ref " << rendererId << std::endl;
		GlCall(glDeleteTextures(1, &rendererId));
	}
	count--;
}