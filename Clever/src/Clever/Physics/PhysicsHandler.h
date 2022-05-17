#pragma once
#include <glm/glm.hpp>
#include "Platform/Object/GameObject.h"

namespace Clever {
	class PhysicsHandler
	{

	struct Direction {
		bool x;
		bool y;
		bool z;
	};

	public:
		void static updatePositions(std::vector<GameObject>& dymanicObjects, std::vector<GameObject>& nonDymanicObjects, std::vector<glm::vec3> accelerations, float ts);
		Direction static willCollide(GameObject& o1, GameObject& o2, glm::vec3 acceleration, float ts);
		bool static areColliding(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 scale1, glm::vec3 scale2);
		void static unstick(Direction directions, GameObject& o1, std::vector<GameObject>&, float ts, bool invert = true);
	};
}