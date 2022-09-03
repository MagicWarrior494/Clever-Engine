#include "cvpch.h"
#include "ColorController.h"

namespace Clever {

	void ColorController::init()
	{
	}

	void ColorController::Update(glm::vec3 colorToSet)
	{

		auto& textures = RenderingData::getInstance().getTextures();

		for (auto& entities : textures)
		{
			for (auto& entity : entities.second)
			{
				entity = colorToSet;
			}
		}
	}
}