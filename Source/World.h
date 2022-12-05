#pragma once

#include "Camera.h"
#include "Input.h"
#include "ShaderProgram.h"

#include <deque>

class World
{
public:
	World();

	static bool InitShared();
	bool Init();
	void Render();
	void Update(float updateTime, Input::InputData* inputData);

private:
	unsigned CalcFrameRate(float frameTime);
	void UpdateCamera(float updateTime, Input::InputData* inputData);
#ifdef IMGUI_ENABLED
	void ImGuiBeginRender();
	void ImGuiRenderStart();
	void ImGuiRenderEnd();
#endif

	static ShaderProgram shaderProgram1;
	unsigned m_VAO = 0;
	unsigned m_VBO = 0;
	unsigned m_EBO = 0;

	glm::mat4 m_modelMat = glm::mat4(1.0f);

	Camera m_camera;

	std::deque<float> m_frameTimes;
	float m_frameTimeTotal = 0;
	unsigned m_frameRate = 0;
};