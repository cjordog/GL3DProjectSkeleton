#pragma once
#include <glm/vec3.hpp>

class Mesh
{
public:
	static glm::vec3* GetCubeVertices();
	static uint8_t* GetCubeIndices();

private:
	static glm::vec3 s_cubeVertices[24];
	static uint8_t s_cubeIndices[36];
};