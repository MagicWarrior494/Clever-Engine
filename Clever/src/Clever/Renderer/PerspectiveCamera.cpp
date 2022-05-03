#include "cvpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtx/transform.hpp>

namespace Clever {
	PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, float fnear, float ffar, glm::vec3 position)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fov), width / height, fnear, ffar)), m_Position(position)
	{
		RecaluclateViewMatrix();
	}

	const void PerspectiveCamera::Translate(Camera_Movement direction, float deltaTime)
	{
		float velocity = m_CameraSpeed * deltaTime;
		if (direction == Camera_Movement::FORWARD)
			m_Position += m_Front * velocity;
		if (direction == Camera_Movement::BACKWARD)
			m_Position -= m_Front * velocity;
		if (direction == Camera_Movement::LEFT)
			m_Position -= m_Right * velocity;
		if (direction == Camera_Movement::RIGHT)
			m_Position += m_Right * velocity;
		if (direction == Camera_Movement::UP)
			m_Position += m_WorldUp * velocity;
		if (direction == Camera_Movement::DOWN)
			m_Position -= m_WorldUp * velocity;
	}

	void PerspectiveCamera::RecaluclateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}

	void PerspectiveCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}

	void PerspectiveCamera::updateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		m_Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
}