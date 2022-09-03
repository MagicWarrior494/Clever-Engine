#include "cvpch.h"
#include "PlatformPhysicsSystem.h"

namespace Clever {

	void PlatformPhysicsSystem::Init()
	{
	}

	void PlatformPhysicsSystem::Update(float dt)
	{
		auto& transforms = RenderingData::getInstance().getTransforms();

		for (auto& entities : RenderingData::getInstance().getRigidBodies())
		{
			int counter = 0;
			for (auto&  entity : entities.second)
			{
				entity.velocity = entity.acceleration * dt;

				RenderingData::getInstance().setTransform(entities.first, counter, glm::translate(transforms.at(entities.first).at(counter), entity.velocity * dt));
				
				counter++;
			}
		}
	}
}