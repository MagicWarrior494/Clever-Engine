#pragma once

#include <glm/glm.hpp>


namespace Clever {

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fov, float width, float height, float fnear, float ffar, glm::vec3 position, glm::vec3 rotation);


		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecaluclateViewMatrix(); }

		const glm::vec3& GetRotation() const { return m_ViewDirection; }
		void SetRotation(const glm::vec3& rotation) { m_ViewDirection = rotation; RecaluclateViewMatrix(); }

		const void Translate(glm::vec3 offset);
		const void Rotate(glm::vec3 direction);

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void RecaluclateViewMatrix();
		const void SetMovementSpeed(float CameraSpeed) { m_CameraSpeed = CameraSpeed; }
		const float GetMovementSpeed() { return m_CameraSpeed; }
		const void SetRotationSpeed(float CameraSpeed) { m_CameraRotationSpeed = CameraSpeed; }
		const float GetRotationSpeed() { return m_CameraRotationSpeed; }
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec3 m_CameraUp = glm::vec3(0,1,0);
		float m_Fov = 65.0f;

		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
		glm::vec3 m_ViewDirection = { 0.0f, 0.0f, 0.0f };
		float m_CameraSpeed = 5.0f;
		float m_CameraRotationSpeed = 0.5f;
	};

}