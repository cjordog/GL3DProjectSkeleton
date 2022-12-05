#include <glad/glad.h>
#include "Window.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(uint width, uint height)
	: m_width(width)
	, m_height(height)
	, m_window(nullptr)
{ }

int Window::Init()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	m_window = glfwCreateWindow(m_width, m_height, "GLVoxel", NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	return 0;
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_window);
}