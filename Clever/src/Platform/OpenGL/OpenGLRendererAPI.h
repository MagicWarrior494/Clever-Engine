#pragma once
#include "Clever/Renderer/RendererAPI.h"
namespace Clever {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void SetDepthTesting() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;
	private:

	};

}