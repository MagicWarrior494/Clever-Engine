#pragma once
#include <Clever.h>

class PlayerManager
{
public:

	PlayerManager()
		: m_Camera(65.0f, 1280.0f, 720.0f, 0.1f, 1000000.0f, glm::vec3(2, 0, 2))
	{

	}

	void OnUpdate(float time)
	{
		glm::vec3 fVector = { 0,0,-1 };
		glm::vec3 frontVector = m_Camera.getFront();
		frontVector.y = 0;

		float fVectorMagnitude = sqrt(pow(fVector.x, 2) + pow(fVector.y, 2) + pow(fVector.z, 2));
		float frontMagnitude = sqrt(pow(frontVector.x, 2) + pow(frontVector.y, 2) + pow(frontVector.z, 2));
		float angle = acos(glm::dot(fVector, m_Camera.getFront()) / (fVectorMagnitude * frontMagnitude));
		if (frontVector.x > 0)
			angle *= -1;

		float velocity = 5;
		glm::vec3 front = m_Camera.getFront();
		front.y = 0;
		glm::vec3 right = m_Camera.getRight();
		glm::vec3 up = m_Camera.getWorldUp();

		glm::vec3 adderVelocity = { 0,0,0 };

		if (Clever::Input::IsKeyPressed(CV_KEY_A))
			m_Camera.Translate(Clever::Camera_Movement::LEFT, time);

		if (Clever::Input::IsKeyPressed(CV_KEY_D))
			m_Camera.Translate(Clever::Camera_Movement::RIGHT, time);

		if (Clever::Input::IsKeyPressed(CV_KEY_W))
			m_Camera.Translate(Clever::Camera_Movement::FORWARD, time);

		if (Clever::Input::IsKeyPressed(CV_KEY_S))
			m_Camera.Translate(Clever::Camera_Movement::BACKWARD, time);

		if (Clever::Input::IsKeyPressed(CV_KEY_SPACE))
			m_Camera.Translate(Clever::Camera_Movement::UP, time);

		if (Clever::Input::IsKeyPressed(CV_KEY_LEFT_SHIFT))
			m_Camera.Translate(Clever::Camera_Movement::DOWN, time);
		
		if (Clever::Input::IsMouseButtonPressed(1) && !m_LockMouse)
		{
			m_LockMouse = true;
			Clever::Input::HideMouse(true);
		}

		if (Clever::Input::IsKeyPressed(CV_KEY_ESCAPE))
		{
			m_LockMouse = false;
			Clever::Input::HideMouse(false);
		}

		if (m_LockMouse && Clever::Input::GetMousePosition() != m_MiddleOfScreen)
		{
			std::pair<float, float> currentMousePos = Clever::Input::GetMousePosition();

			if (m_FirstMouse)
			{
				m_LastX = currentMousePos.first;
				m_LastY = currentMousePos.second;
				m_FirstMouse = false;
			}

			float xoffset = currentMousePos.first - m_LastX;
			float yoffset = m_LastY - currentMousePos.second; //Reversed since y-coordinates go from bottom to top

			if (currentMousePos.first < 0 || currentMousePos.first > m_MiddleOfScreen.first * 2 || currentMousePos.second < 0 || currentMousePos.second > m_MiddleOfScreen.second * 2)
			{
				Clever::Input::SetMousePos(m_MiddleOfScreen.first, m_MiddleOfScreen.second);
				m_LastX = m_MiddleOfScreen.first;
				m_LastY = m_MiddleOfScreen.second;
			}
			else
			{
				m_LastX = currentMousePos.first;
				m_LastY = currentMousePos.second;
			}
			m_Camera.ProcessMouseMovement(xoffset, yoffset);
		}
	}

	Clever::PerspectiveCamera getCamera()
	{
		return m_Camera;
	}

	bool getMouseLockedState()
	{
		return m_LockMouse;
	}

	void setMouseLockedState(bool val)
	{
		m_LockMouse = val;
	}

private:
	Clever::PerspectiveCamera m_Camera;
	bool m_LockMouse = true;
	std::pair<float, float> m_MiddleOfScreen = std::pair<float, float>(1280.0f / 2, 720.0f / 2);
	float m_LastX = 1280.0f / 2;
	float m_LastY = 720.0f / 2;
	bool m_FirstMouse = true;
};