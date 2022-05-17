#include "cvpch.h"
#include "GameObject.h"
namespace Clever {

	GameObject::GameObject(glm::vec3 position)
		: m_Position(position)
	{
	}

	GameObject::GameObject(ObjectData& objectMesh)
		: m_ObjectMesh(objectMesh)
	{
	}

	GameObject::GameObject(ObjectData& objectMesh, glm::vec3 position)
		: m_ObjectMesh(objectMesh), m_Position(position)
	{
	}

	GameObject::GameObject(ObjectData& objectMesh, glm::vec3 position, glm::vec3 scale)
		: m_ObjectMesh(objectMesh), m_Position(position), m_Scale(scale)
	{
	}

	GameObject::GameObject(ObjectData& objectMesh, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
		: m_ObjectMesh(objectMesh), m_Position(position), m_Rotation(rotation), m_Scale(scale)
	{
	}

	GameObject::GameObject(ObjectData& objectMesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color)
		: m_ObjectMesh(objectMesh), m_Position(position), m_Rotation(rotation), m_Scale(scale), m_Color(color)
	{
	}

}