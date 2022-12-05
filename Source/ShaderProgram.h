#pragma once


class ShaderProgram
{
public:
	ShaderProgram() = default;
	ShaderProgram(const char* vShader, const char* fShader);

	void Use();

private:
	enum ShaderType {
		Vertex = 0,
		Fragment = 1,
	};
	unsigned CompileShader(const char* shaderPath, ShaderType shaderType);
	
	unsigned m_id = 0;
};