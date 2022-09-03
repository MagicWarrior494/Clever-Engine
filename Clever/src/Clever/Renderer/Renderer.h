#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"
#include "Shader.h"
#include "Platform/Object/ObjectData.h"

namespace Clever {

	class Renderer
	{
	public:
		static void BeginScene(PerspectiveCamera& camera);

		static void EndScene();

		static void Submit(const Ref<Shader>& shader, Ref<ObjectData> gameObject, uint32_t size);
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}