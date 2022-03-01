#include "cvpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Clever {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}