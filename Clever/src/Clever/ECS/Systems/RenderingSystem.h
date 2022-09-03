#pragma once
#include "Clever/ECS/Handlers/System.h"
#include "Clever/Renderer/PerspectiveCamera.h"
#include "Clever/ECS/Handlers/Coordinator.h"
#include "Clever/Renderer/RenderCommand.h"
#include "Clever/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Clever/Application.h"
#include "Clever/ECS/Components/Components.h"
#include <glm/gtc/type_ptr.hpp>
#include "Clever/ECS/DataHandelers/RenderingData.h"
#include <unordered_map>

namespace Clever {

	class RenderingSystem : public System
	{
	public:
		void init();

		void Update(float dt, PerspectiveCamera camera);
	};
}