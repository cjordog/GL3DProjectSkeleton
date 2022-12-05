#include "Input.h"
#include "RenderSettings.h"
#include <GLFW/glfw3.h>

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

static glm::vec2 s_mouseWheel = glm::vec2(0, 0);

// used to process events only once, since it gets called once per key event, instead of polling in ProcessEvents
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		RenderSettings& renderSettings = RenderSettings::Get();
		RenderSettings::DrawMode newMode = renderSettings.m_drawMode == RenderSettings::DrawMode::Wireframe ? RenderSettings::DrawMode::Triangles : RenderSettings::DrawMode::Wireframe;
		renderSettings.m_drawMode = RenderSettings::DrawMode(newMode);
	}

	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		RenderSettings& renderSettings = RenderSettings::Get();
		renderSettings.greedyMesh = !renderSettings.greedyMesh;
		renderSettings.deleteMesh = true;
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		RenderSettings& renderSettings = RenderSettings::Get();
		renderSettings.renderDebugWireframes = !renderSettings.renderDebugWireframes;
	}
}

static void MouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	s_mouseWheel = {xoffset, yoffset};
}

Input::Input(Window* w)
	: m_window(w)
{
	GLFWwindow* glfwWin = w->GetGLFWWindow();
	glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(glfwWin, KeyCallback);
	glfwSetScrollCallback(glfwWin, MouseWheelCallback);
}

void Input::ProcessInput()
{
	ZoneScoped;
	GLFWwindow* glfwWin = m_window->GetGLFWWindow();
	if (glfwGetKey(glfwWin, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(glfwWin, true);

	m_inputData.Reset();

	if (glfwGetKey(glfwWin, GLFW_KEY_W) == GLFW_PRESS)
		m_inputData.m_moveInput.z -= 1.0f;
	if (glfwGetKey(glfwWin, GLFW_KEY_S) == GLFW_PRESS)
		m_inputData.m_moveInput.z += 1.0f;
	if (glfwGetKey(glfwWin, GLFW_KEY_A) == GLFW_PRESS)
		m_inputData.m_moveInput.x -= 1.0f;
	if (glfwGetKey(glfwWin, GLFW_KEY_D) == GLFW_PRESS)
		m_inputData.m_moveInput.x += 1.0f;
	if (glfwGetKey(glfwWin, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_inputData.m_moveInput.y += 1.0f;
	if (glfwGetKey(glfwWin, GLFW_KEY_Z) == GLFW_PRESS)
		m_inputData.m_moveInput.y -= 1.0f;
	
	m_inputData.m_mouseWheel = s_mouseWheel;
	s_mouseWheel = glm::vec2(0, 0);

#ifdef IMGUI_ENABLED
	//probably could be set once on press and release
	if (glfwGetKey(glfwWin, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) 
	{
		m_inputData.m_disableMouseLook = true;
		glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		m_inputData.m_disableMouseLook = false;
		glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
#endif

	double xpos, ypos;
	glfwGetCursorPos(glfwWin, &xpos, &ypos);
	
	if (!m_isFirstFrame)
	{
		m_inputData.m_mouseInput.x = float(xpos - m_lastCursorPosX);
		m_inputData.m_mouseInput.y = float(ypos - m_lastCursorPosY);
	}

	m_lastCursorPosX = xpos;
	m_lastCursorPosY = ypos;

	m_inputData.m_mouseButtons.x = (glfwGetMouseButton(glfwWin, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS);
	m_inputData.m_mouseButtons.y = (glfwGetMouseButton(glfwWin, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS);

	m_isFirstFrame = false;
}

void Input::Poll()
{
	glfwPollEvents();
}
