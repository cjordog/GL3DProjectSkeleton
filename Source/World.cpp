#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "World.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GX.h"
#include "Mesh.h"

#ifdef IMGUI_ENABLED
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#endif

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

ShaderProgram World::shaderProgram1;

World::World()
	: m_camera(glm::vec3(0, 0, -10), 0, 90.0f)
{

}

bool World::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	constexpr int vertexBindingPoint = 0;
	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, vertexBindingPoint);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(float), (float*)Mesh::GetCubeVertices(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(uint8_t), Mesh::GetCubeIndices(), GL_STATIC_DRAW);

	return true;
}

bool World::InitShared()
{
	shaderProgram1 = ShaderProgram("test1.vs.glsl", "test1.fs.glsl");
	return true;
}

void World::Render()
{
	ZoneScoped;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef IMGUI_ENABLED
	ImGuiBeginRender();
#endif

	shaderProgram1.Use();
	glBindVertexArray(m_VAO);
	glBindVertexBuffer(0, m_VBO, 0, sizeof(GX::VertexP));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glUniformMatrix4fv(0, 1, GL_FALSE, &glm::mat4(m_camera.GetViewMatrix() * m_modelMat)[0][0]);
	glUniformMatrix4fv(1, 1, GL_FALSE, &m_camera.GetProjMatrix()[0][0]);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);

#ifdef IMGUI_ENABLED
	ImGuiRenderStart();
	ImGuiRenderEnd();
#endif
}

void World::Update(float updateTime, Input::InputData* inputData)
{
	ZoneScoped;
	UpdateCamera(updateTime, inputData);
	CalcFrameRate(updateTime);
}

constexpr float FRAMERATE_MS = 1000.0f;
unsigned World::CalcFrameRate(float frameTime)
{
	m_frameTimes.push_back(frameTime);
	m_frameTimeTotal += frameTime;

	while (m_frameTimeTotal > FRAMERATE_MS)
	{
		m_frameTimeTotal -= m_frameTimes.front();
		m_frameTimes.pop_front();
	}

	m_frameRate = unsigned(m_frameTimes.size() / FRAMERATE_MS * 1000.f);
	return m_frameRate;
}

void World::UpdateCamera(float updateTime, Input::InputData* inputData)
{
	m_camera.FrameStart();
	if (!inputData->m_disableMouseLook)
	{
		glm::vec3 newPos = m_camera.GetPosition() + (glm::vec3(m_camera.GetForward() * -inputData->m_moveInput.z + m_camera.GetRight() * inputData->m_moveInput.x + glm::vec3(0, inputData->m_moveInput.y, 0)) * updateTime / 1000.0f * 10.0f);
		m_camera.Transform(newPos, -inputData->m_mouseInput.y * 0.5f, inputData->m_mouseInput.x * 0.5f);
	}
}

#ifdef IMGUI_ENABLED
void World::ImGuiBeginRender()
{
	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void World::ImGuiRenderStart()
{
	// render your GUI
	ImGui::Begin("Demo window");
	ImGui::Text("Framerate: %d", m_frameRate);
	glm::vec3 cameraPos = m_camera.GetPosition();
	ImGui::Text("Position x:%.3f y:%.3f z:%.3f", cameraPos.x, cameraPos.y, cameraPos.z);
}

void World::ImGuiRenderEnd()
{
	//ImGui::ShowDemoWindow();
	ImGui::End();

	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
#endif