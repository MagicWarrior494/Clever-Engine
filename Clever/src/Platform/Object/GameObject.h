#pragma once
#include <glm/glm.hpp>
#include "ObjectData.h"

namespace Clever {

	class GameObject
	{
	public:
		//For testing with empty game objects
		GameObject(glm::vec3 position);

		GameObject(ObjectData& objectMesh);
		GameObject(ObjectData& objectMesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
		GameObject(ObjectData& objectMesh, glm::vec3 position);
		GameObject(ObjectData& objectMesh, glm::vec3 position, glm::vec3 scale);
		GameObject(ObjectData& objectMesh, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);

		inline Clever::Ref<Clever::VertexArray> getVertexArray() const { return m_ObjectMesh.getVertexArray(); }
		Clever::Ref<Clever::Shader> getShader() const { return m_ObjectMesh.getShader().getShader(); }
		inline void setColor(glm::vec3 color) { m_Color = color; }

		void step(glm::vec3 acceleration, float ts)  
		{
			m_Velocity += (acceleration * ts);
			m_Position += (m_Velocity * ts);
		}

		void reset(glm::vec3 dir) {
			if (dir.x > 0)
				m_Velocity.x = 0;
			if (dir.y > 0)
				m_Velocity.y = 0;
			if (dir.z > 0)
				m_Velocity.z = 0;
		}

		glm::vec3 m_Scale = { 1,1,1 };
		glm::vec3 m_Position = { 0,0,0 };
		glm::vec3 m_Rotation = { 0,0,0 };
		glm::vec3 m_Color = { 0.2f, 0.3f, 0.8f };

		glm::vec3 m_Velocity = { 0,0,0 };
		glm::vec3 m_ColliderScale = m_Scale;
		bool m_dymanic = false;

	private:
		ObjectData& m_ObjectMesh = ObjectData();
		//Ref<ObjectTexture> objectTexture;
	};
}

