#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Clever {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void SetDepthTesting() = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;


	};

}