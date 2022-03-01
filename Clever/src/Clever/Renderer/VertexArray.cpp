#include "cvpch.h"
#include"VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Clever {

	VertexArray* VertexArray::Create() 
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:   CV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		CV_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

}