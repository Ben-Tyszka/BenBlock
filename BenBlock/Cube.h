#pragma once
#include "Shader.h"
#include "Camera.h"
#include "BMPLoader.h"
class Cube
{
public:
	Cube(Camera cam, const char* tex_path, glm::vec3 position);
	void Render();
	void setPosition(glm::vec3 position);
	Camera cam;
	~Cube();
private:
	GLuint vertexBuffer, uvBuffer, ibo_cube_elements;
	Shader s;
	glm::mat4 mvp;
	glm::mat4 Model;
	GLuint tex;
};

