#pragma once

#include <glm/vec3.hpp>

struct GLFWwindow;

class GX
{
public:
	struct VertexPCN
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 normal;
	};

	struct VertexP
	{
		glm::vec3 position;
	};

	static int GLADInit();
	static void SwapBuffers(GLFWwindow* window);
};