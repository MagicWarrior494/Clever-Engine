#pragma once
#include "Platform/Object/ObjectData.h"


namespace Clever {

	struct RigidBodyComponent
	{
		glm::vec3 velocity;
		glm::vec3 acceleration;
	};

	struct PointsPositionComponent
	{
		glm::vec3 firstPoint;
		glm::vec3 secondPoint;
		bool travelingToSecondPoint;
		float speed;
	};

	struct CollisionBoxComponent
	{
		glm::vec3 firstCorner;
		glm::vec3 secondCorner;
		float maxSize;
	};

	struct TransformComponent
	{
		uint32_t transformIndex;
	};

	struct ColorComponent
	{
		uint32_t textureIndex;
	};

	struct MeshComponent
	{
		Ref<ObjectData> MeshData;
	};
}