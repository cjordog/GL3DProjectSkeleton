#include "Mesh.h"

glm::vec3 Mesh::s_cubeVertices[24] =
{
	{1.0f,	1.0f,	0.0f},
	{1.0f,	0.0f,	0.0f},
	{1.0f,	0.0f,	1.0f},
	{1.0f,	1.0f,	1.0f},

	{0.0f,	1.0f,	1.0f},
	{0.0f,	0.0f,	1.0f},
	{0.0f,	0.0f,	0.0f},
	{0.0f,	1.0f,	0.0f},

	{1.0f,	1.0f,	0.0f},
	{1.0f,	1.0f,	1.0f},
	{0.0f,	1.0f,	1.0f},
	{0.0f,	1.0f,	0.0f},

	{0.0f,	0.0f,	0.0f},
	{0.0f,	0.0f,	1.0f},
	{1.0f,	0.0f,	1.0f},
	{1.0f,	0.0f,	0.0f},

	{1.0f,	1.0f,	1.0f},
	{1.0f,  0.0f,	1.0f},
	{0.0f,	0.0f,	1.0f},
	{0.0f,	1.0f,	1.0f},

	{0.0f,	1.0f,	0.0f},
	{0.0f,	0.0f,	0.0f},
	{1.0f,	0.0f,	0.0f},
	{1.0f,	1.0f,	0.0f},
};

uint8_t Mesh::s_cubeIndices[36] =
{
	0, 3, 1,
	1, 3, 2,
	4, 7, 5,
	5, 7, 6,
	8, 11, 9,
	9, 11, 10,
	12, 15, 13,
	13, 15, 14,
	16, 19, 17,
	17, 19, 18,
	20, 23, 21,
	21, 23, 22,
};

glm::vec3* Mesh::GetCubeVertices()
{
	return s_cubeVertices;
}

uint8_t* Mesh::GetCubeIndices()
{
	return s_cubeIndices;
}
