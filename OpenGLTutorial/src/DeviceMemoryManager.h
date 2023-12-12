#pragma once

#include <iostream>
#include <unordered_map>

#include <GL/glew.h>

#include "Debug.h"

class DeviceMemoryManager
{
private:
	static DeviceMemoryManager* instance;

	std::unordered_map<unsigned int, unsigned int> bufferRefCount;
	std::unordered_map<unsigned int, unsigned int> vertexArrRefCount;
	std::unordered_map<unsigned int, unsigned int> shaderRefCount;
	std::unordered_map<unsigned int, unsigned int> textureRefCount;

public:
	DeviceMemoryManager();
	~DeviceMemoryManager();

	static inline DeviceMemoryManager& GetInstance() { return *instance; }

	void AddVertexBuffRef(unsigned int rendererId);
	void AddVertexArrRef(unsigned int rendererId);
	void AddIndexRef(unsigned int rendererId);
	void AddShaderRef(unsigned int rendererId);
	void AddTextureRef(unsigned int rendererId);

	void RemoveVertexBuffRef(unsigned int rendererId);
	void RemoveVertexArrRef(unsigned int rendererId);
	void RemoveIndexRef(unsigned int rendererId);
	void RemoveShaderRef(unsigned int rendererId);
	void RemoveTextureRef(unsigned int rendererId);
};