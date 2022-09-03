#pragma once

//For use by Hazel applications

#include "Clever/Application.h"
#include "Clever/Layer.h"
#include "Clever/ImGui/ImGuiLayer.h"

#include "Clever/Core/Timestep.h"

#include "Clever/Log.h"
#include "Clever/MouseButtonCodes.h"
#include "Clever/KeyCodes.h"

#include "Clever/Renderer/Renderer.h"
#include "Clever/Renderer/RenderCommand.h"
#include "Clever/Renderer/Buffer.h"
#include "Clever/Renderer/Shader.h"
#include "Clever/Renderer/Texture.h"
#include "Clever/Renderer/VertexArray.h"

#include "Platform/Object/ObjectData.h"
#include "Platform/Object/CompiledShader.h"
#include "Platform/Networking/Client.h"

//ECS STUFF ---------------------
#include "Clever/ECS/Handlers/Coordinator.h"
#include "Clever/ECS/Components/Components.h"
#include "Clever/ECS/Systems/RenderingSystem.h"
#include "Clever/ECS/Systems/ColorController.h"
#include "Clever/ECS/Systems/PlatformPhysicsSystem.h"
#include "Clever/ECS/Systems/TravelBetweenPointsSystem.h"

//-------------------------------

#include "Clever/Renderer/OrthographicCamera.h"


#include "Clever/input.h"
//Entry Point -------------------
#include "Clever/EntryPoint.h"
//-------------------------------

//TEMP  -------------------------
#include "glm/gtx/string_cast.hpp"
//-------------------------------