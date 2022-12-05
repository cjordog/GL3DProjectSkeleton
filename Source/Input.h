#pragma once
#include "Window.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class Input
{
public:
	struct InputData
	{
		void Reset()
		{
			m_moveInput = glm::vec3(0.0f);
			m_mouseInput = glm::vec2(0.0f);
			m_mouseButtons = glm::vec2(0.0f);
		}

		bool m_disableMouseLook = false;

		glm::vec3 m_moveInput = glm::vec3(0.0f);
		glm::vec2 m_mouseInput = glm::vec2(0.0f);
		glm::vec2 m_mouseButtons = glm::vec2(0.0f);
		glm::vec2 m_mouseWheel = glm::vec2(0.0f);
	};

	Input(Window* w);
	InputData* GetInputData(){ return &m_inputData; };
	void ProcessInput();
	void ProcessMousePos(GLFWwindow* window, double xpos, double ypos);
	void Poll();
	//void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	Window* m_window;
	InputData m_inputData;
	double m_lastCursorPosX = 0;
	double m_lastCursorPosY = 0;

	bool m_isFirstFrame = true;
};