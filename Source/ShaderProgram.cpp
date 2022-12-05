#include "ShaderProgram.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

ShaderProgram::ShaderProgram(const char* vShader, const char* fShader)
{
	unsigned vs = CompileShader(vShader, ShaderType::Vertex);
	unsigned fs = CompileShader(fShader, ShaderType::Fragment);

	if (vs != -1 && fs != -1)
	{
		m_id = glCreateProgram();

		glAttachShader(m_id, vs);
		glAttachShader(m_id, fs);
		glLinkProgram(m_id);

		int success;
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(m_id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
			return;
		}
	}
	else
	{
		return;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void ShaderProgram::Use()
{
	glUseProgram(m_id);
}

unsigned ShaderProgram::CompileShader(const char* shaderPath, ShaderType shaderType)
{
	unsigned shader;

	char shaderP[256];
	strcpy_s(shaderP, "../Source/Shaders/");
	strcat_s(shaderP, shaderPath);

	switch (shaderType)
	{
	case Vertex:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case Fragment:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		return -1;
		break;
	}

	std::string shaderCode;
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		shaderFile.open(shaderP);
		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return -1;
	}

	const GLchar* shaderCodeCStr = shaderCode.c_str();
	glShaderSource(shader, 1, &shaderCodeCStr, NULL);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		return -1;
	}

	return shader;
}
