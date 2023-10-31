#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Debug.h"

struct ShaderSource
{
	std::string vertexSrc;
	std::string fragmentSrc;
};

class Shader
{
private:
	unsigned int myRendererId;
	std::string myFilepath;
	std::unordered_map<std::string, int> myUniformLocCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set Uniforms
	void SetUniform1i(const std::string& name, const int value);
	void SetUniform4f(const std::string& name, const glm::mat4& matrix);

private:
	int GetUniformLocation(const std::string& name);

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderSource ParseShader();
	unsigned int CompileShader(const std::string& source, unsigned int type);
};

