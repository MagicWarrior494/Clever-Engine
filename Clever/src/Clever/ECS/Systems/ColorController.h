#include "Clever/ECS/Handlers/System.h"
#include "Clever/ECS/Handlers/Coordinator.h"
#include "Clever/Application.h"
#include "Clever/ECS/DataHandelers/RenderingData.h"
#include "Clever/ECS/Components/Components.h"

namespace Clever {

	class ColorController : public System
	{
	public:
		void init();

		void Update(glm::vec3 colorToSet);

	};
}