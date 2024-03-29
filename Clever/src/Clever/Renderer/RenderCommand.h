#pragma once
#include "RendererAPI.h"

namespace Clever {

	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void SetDepthTesting(const bool depthTesting)
		{
			s_RendererAPI->SetDepthTesting();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count)
		{
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};

}