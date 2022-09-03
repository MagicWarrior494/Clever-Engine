#include "cvpch.h"
#include "TravelBetweenPointsSystem.h"
namespace Clever {
	void TravelBetweenPointsSystem::Init()
	{
		/*for (EntityID entity : m_Entities)
		{
			TransformComponent& tr = Application::Get().getCoordinator().GetComponent<TransformComponent>(entity);
			PointsPositionComponent& pp = Application::Get().getCoordinator().GetComponent<PointsPositionComponent>(entity);
			tr.position = pp.firstPoint;
		}*/
	}

	void TravelBetweenPointsSystem::Update(float dt)
	{

		auto& tranforms = RenderingData::getInstance().getTransforms();
		auto& rigidBodies = RenderingData::getInstance().getRigidBodies();
		auto& pointPositions = RenderingData::getInstance().getPointPositions();

		for (auto& entities : rigidBodies)
		{
			int counter = 0;
			for (auto& entity : entities.second)
			{
				glm::vec3 accelerationDirection = { 0,0,0 };
				PointsPositionComponent& ppc = pointPositions.at(entities.first).at(counter);
				RigidBodyComponent& rbc = rigidBodies.at(entities.first).at(counter);

				const float* pSource = (const float*)glm::value_ptr(tranforms.at(entities.first).at(counter));

				glm::vec3 position = { pSource[12], pSource[13] , pSource[14] };
				if (ppc.travelingToSecondPoint)
				{
					accelerationDirection = ppc.secondPoint - ppc.firstPoint;
					if (glm::distance(ppc.firstPoint, ppc.secondPoint) < glm::distance(position, ppc.firstPoint))
					{
						if (glm::dot(rbc.acceleration, rbc.velocity) > 0)
						{
							ppc.travelingToSecondPoint = !ppc.travelingToSecondPoint;
							rbc.velocity = { 0,0,0 };
						}
					}
				}
				else {
					accelerationDirection = ppc.firstPoint - ppc.secondPoint;
					if (glm::distance(ppc.firstPoint, ppc.secondPoint) < glm::distance(position, ppc.secondPoint))
					{
						if (glm::dot(rbc.acceleration, rbc.velocity) > 0)
						{
							ppc.travelingToSecondPoint = !ppc.travelingToSecondPoint;
							rbc.velocity = { 0,0,0 };
						}
					}
				}

				//accelerationDirection = glm::normalize(accelerationDirection);
				rbc.acceleration = accelerationDirection * ppc.speed;
				counter++;
			}
		}
	}
}