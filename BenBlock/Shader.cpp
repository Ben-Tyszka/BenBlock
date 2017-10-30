#include "stdafx.h"
#include "Shader.h"


Shader::Shader()
{
	vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	File file_vert = File::File("test.vert");
	File file_frag = File::File("test.frag");

	char const * VertexSourcePointer = file_vert.text.c_str();
	char const * FragSourcePointer = file_frag.text.c_str();

	glShaderSource(vertShaderID, 1, &VertexSourcePointer, NULL);
	glShaderSource(fragShaderID, 1, &FragSourcePointer, NULL);

	glCompileShader(vertShaderID);
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vertShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	glCompileShader(fragShaderID);

	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fragShaderID, InfoLogLength, NULL, &FragShaderErrorMessage[0]);
		printf("%s\n", &FragShaderErrorMessage[0]);
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertShaderID);
	glAttachShader(programID, fragShaderID);
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(programID, vertShaderID);
	glDetachShader(programID, fragShaderID);

	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);

}


Shader::~Shader()
{

}

void Shader::Bind(glm::mat4 mvp)
{
	glUseProgram(programID);
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

void Shader::Unbind()
{
	glUseProgram(0);
}
