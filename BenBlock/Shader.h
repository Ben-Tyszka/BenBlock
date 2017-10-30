#pragma once

#include "File.h"

class Shader
{
public:
	Shader();
	~Shader();
	void Bind(glm::mat4 mvp);
	void Unbind();
	GLuint programID;
private:
	GLuint vertShaderID;
	GLuint fragShaderID;
};

