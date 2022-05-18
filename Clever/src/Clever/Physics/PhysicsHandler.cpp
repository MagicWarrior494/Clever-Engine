#include "cvpch.h"
#include "PhysicsHandler.h"

namespace Clever {

	void PhysicsHandler::updatePositions(std::vector<GameObject>& dymanicObjects, std::vector<GameObject>& nonDymanicObjects, std::vector<glm::vec3> accelerations, float ts)
	{	
		glm::vec3 totalAcceleration = {0,0,0};
		
		for (glm::vec3 acceleration : accelerations)
		{
			totalAcceleration += acceleration;
		}

		for (GameObject& dymanicGo : dymanicObjects)
		{
			Direction collidingDirection = { false, false, false };
			for (GameObject& staticGo : nonDymanicObjects)
			{
				Direction result = willCollide(dymanicGo, staticGo, totalAcceleration, ts);
				//CV_CORE_TRACE("The NEW result is: {0}, {1}, {2}", result.x, result.y, result.z);
				if (result.x)
				{
					collidingDirection.x = true;
				}
				if (result.y)
				{
					collidingDirection.y = true;
				}
				if (result.z)
				{
					collidingDirection.z = true;
				}
				if (dymanicGo.m_dymanic)
					staticGo.step(totalAcceleration, ts);
			}

			glm::vec3 movementDirection = { 0,0,0 };
			if (!collidingDirection.x)
			{
				movementDirection.x = totalAcceleration.x;
			}
			if (!collidingDirection.y)
			{
				movementDirection.y = totalAcceleration.y;
			}
			if (!collidingDirection.z)
			{
				movementDirection.z = totalAcceleration.z;
			}
			if(collidingDirection.x || collidingDirection.y || collidingDirection.z)
				unstick(collidingDirection, dymanicGo, nonDymanicObjects, movementDirection, ts);
			dymanicGo.step(movementDirection, ts);
			
		}
	}

	PhysicsHandler::Direction PhysicsHandler::willCollide(GameObject& o1, GameObject& o2, glm::vec3 acceleration, float ts)
	{
		glm::vec3 o1NextVelocity = o1.m_Velocity + (acceleration * ts);

		glm::vec3 o1NextPositionX = o1.m_Position + glm::vec3((o1NextVelocity * ts).x, 0, 0);

		glm::vec3 o1NextPositionY = o1.m_Position + glm::vec3(0, (o1NextVelocity * ts).y, 0);

		glm::vec3 o1NextPositionZ = o1.m_Position + glm::vec3(0, 0, (o1NextVelocity * ts).z);

		bool resultX = areColliding(o1NextPositionX, o2.m_Position, o1.m_ColliderScale, o2.m_ColliderScale);
		bool resultY = areColliding(o1NextPositionY, o2.m_Position, o1.m_ColliderScale, o2.m_ColliderScale);
		bool resultZ = areColliding(o1NextPositionZ, o2.m_Position, o1.m_ColliderScale, o2.m_ColliderScale);
		
		return {resultX, resultY, resultZ};
	}
	bool PhysicsHandler::areColliding(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 scale1, glm::vec3 scale2)
	{
		glm::vec3 o1Max = pos1 + scale1;
		glm::vec3 o1Min = pos1 - scale1;
		glm::vec3 o2Max = pos2 + scale2;
		glm::vec3 o2Min = pos2 - scale2;
		bool result = (o1Min.x <= o2Max.x && o1Max.x >= o2Min.x) && 
				(o1Min.y <= o2Max.y && o1Max.y >= o2Min.y) &&
				(o1Min.z <= o2Max.z && o1Max.z >= o2Min.z);
		return result;
	}
	void PhysicsHandler::unstick(Direction directions, GameObject& dynamicGo, std::vector<GameObject>& staticGos, glm::vec3 acceleration, float ts, bool invert)
	{
		glm::vec3 resetDirection = { 0,0,0 };
		glm::vec3 newVelocity = {0,0,0};
		if (invert)
		{
			if (directions.x)
			{
				newVelocity.x = -dynamicGo.m_Velocity.x;
				resetDirection.x = 1;
			}
			if (directions.y)
			{
				newVelocity.y = -dynamicGo.m_Velocity.y;
				resetDirection.y = 1;
			}
			if (directions.z)
			{
				newVelocity.z = -dynamicGo.m_Velocity.z;
				resetDirection.z = 1;
			}
		}

		Direction totalResult = {false, false, false};
		dynamicGo.stepCustomVelocity(newVelocity, ts);
		for (GameObject& staticgo : staticGos)
		{
			Direction result = willCollide(dynamicGo, staticgo, {0,0,0}, ts);
			totalResult.x = totalResult.x && result.x;
			totalResult.y = totalResult.y && result.y;
			totalResult.z = totalResult.z && result.z;
		}
		if (totalResult.x || totalResult.y || totalResult.z)
		{
			unstick(totalResult, dynamicGo, staticGos, acceleration, ts, false);
		}
		if (invert)
		{
			dynamicGo.reset(resetDirection);
		}
	}
}