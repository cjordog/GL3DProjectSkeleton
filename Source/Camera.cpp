#include "Camera.h"

Camera::Camera(glm::vec3 pos, float pitch, float yaw)
{
	m_position = pos;
	m_pitch = pitch;
	m_yaw = yaw;

	glm::vec3 direction;
	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction = glm::normalize(direction);

	m_viewMatrix = glm::lookAt(m_position, m_position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
	m_projMatrix = glm::perspective(m_fovX / m_aspectRatio, m_aspectRatio, m_nearClip, m_farClip);
}

void Camera::Transform(glm::vec3 newPos, float pitchDelta, float yawDelta)
{
	//if (glm::length(posDelta) == 0 && pitchDelta == 0 && yawDelta == 0)
	//	return;

	m_yaw += yawDelta;
	m_pitch += pitchDelta;

	constexpr float maxAngle = 89.0f;
	m_pitch = glm::clamp(m_pitch, -maxAngle, maxAngle);

	m_forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_forward.y = sin(glm::radians(m_pitch));
	m_forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_forward = glm::normalize(m_forward);
	m_right = (normalize(cross(m_forward, worldUp)));
	m_up = (cross(m_right, m_forward));

	 //TODO:: this is wrong. need to m_viewMatrix doesnt get moved by posDelta this frame.
	m_position = newPos;
	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, worldUp);
	m_projMatrix = glm::perspective(m_fovX / m_aspectRatio, m_aspectRatio, m_nearClip, m_farClip);

	m_halfVSide = m_farClip * tanf(GetFovY() * 0.5f);
	m_halfHSide = m_halfVSide * m_aspectRatio;
	
	m_movedThisFrame = true;
}

void Camera::FrameStart()
{
	m_movedThisFrame = false;
}
