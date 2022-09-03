#pragma once
#include "Clever/ECS/Handlers/System.h"
#include "Clever/Application.h"
#include "Clever/ECS/DataHandelers/RenderingData.h"
#include <glm/gtc/type_ptr.hpp>
#include "Clever/ECS/Components/Components.h"


namespace Clever {

	class TravelBetweenPointsSystem : public System
	{
	public:
		void Init();

		void Update(float dt);

	};
}