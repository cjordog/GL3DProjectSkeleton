#pragma once
#include <GLFW/glfw3.h>

typedef unsigned int uint;

class Window
{
public:
	Window(uint width, uint height);

	int Init();
	bool ShouldClose();

	uint GetWidth() { return m_width; }
	uint GetHeight() { return m_height; }
	GLFWwindow* GetGLFWWindow() { return m_window; }

private:
	uint m_width;
	uint m_height;

	GLFWwindow* m_window;
};