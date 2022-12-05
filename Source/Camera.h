#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 pos, float pitch, float yaw);

	void Transform(glm::vec3 newPos, float pitchDelta, float yawDelta);
	void CalculateFrustum();

	const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
	const glm::mat4& GetProjMatrix() const { return m_projMatrix; }
	const glm::vec3& GetPosition() const { return m_position; }
	const glm::vec3& GetForward() const { return m_forward; }
	const glm::vec3& GetRight() const { return m_right; }
	float GetAspectRatio() const { return m_aspectRatio; }
	float GetFovX() const { return m_fovX; }
	float GetFovY() const { return m_fovX / m_aspectRatio; }
	float GetNearClip() const { return m_nearClip; }
	float GetFarClip() const { return m_farClip; }

	void FrameStart();

private:
	glm::vec3 m_position = glm::vec3(0);
	glm::mat4 m_viewMatrix = glm::mat4(1);
	glm::mat4 m_projMatrix = glm::mat4(1);

	float m_pitch = 0.0f;
	float m_yaw = 90.0f;
	glm::vec3 m_forward = glm::vec3(0);
	glm::vec3 m_right = glm::vec3(0);
	glm::vec3 m_up = glm::vec3(0);

	float m_aspectRatio = 4.0f / 3.0f;
	float m_fovX = glm::radians(90.0f);
	float m_nearClip = 0.1f;
	float m_farClip = 10000.f;

	float m_halfVSide = 0;
	float m_halfHSide = 0;

	bool m_movedThisFrame = true;
};