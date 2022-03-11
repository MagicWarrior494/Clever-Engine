#include "cvpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtx/transform.hpp>

namespace Clever {
	PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, float fnear, float ffar, glm::vec3 position, glm::vec3 viewDirection)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fov), width / height, fnear, ffar)), m_Position(position), m_ViewDirection(viewDirection)
	{
		RecaluclateViewMatrix();
	}

	const void PerspectiveCamera::Translate(glm::vec3 offset)
	{
		m_Position += m_CameraSpeed * m_ViewDirection * offset.z;
		m_Position += m_CameraSpeed * glm::cross(m_ViewDirection, m_CameraUp) * offset.x;
		m_Position += m_CameraSpeed * m_CameraUp * offset.y;
	}

	const void PerspectiveCamera::Rotate(glm::vec3 direction)
	{
		glm::vec3 toRotateAround = glm::cross(m_ViewDirection, m_CameraUp);
		glm::mat4 rotator = glm::rotate(direction.y * m_CameraRotationSpeed, m_CameraUp) *
			glm::rotate(direction.x * m_CameraRotationSpeed, toRotateAround);

		m_ViewDirection = glm::mat3(rotator) * m_ViewDirection;
	}

	void PerspectiveCamera::RecaluclateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_ViewDirection, m_CameraUp);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}
}