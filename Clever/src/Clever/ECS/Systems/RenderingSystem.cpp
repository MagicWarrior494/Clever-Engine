#include "cvpch.h"
#include "RenderingSystem.h"


namespace Clever {

	void RenderingSystem::init()
	{
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::SetDepthTesting(true);


	}
	void RenderingSystem::Update(float dt, PerspectiveCamera camera)
	{

		Clever::RenderCommand::Clear();

		camera.RecaluclateViewMatrix();

		Clever::Renderer::BeginScene(camera);
		
		
		auto const& transforms = RenderingData::getInstance().getTransforms();
		auto const& textures = RenderingData::getInstance().getTextures();

		int counter = 0;
		for (auto const& entity : transforms)
		{
			entity.first->recalculateInstancedList(entity.second);
			entity.first->UpdatedColors(textures.at(entity.first));
			Clever::Ref<Clever::Shader> shader = entity.first->getShader().getShader();
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->Bind();
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3("u_LightColor", {0.5, 0.5, 0.5});
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3("u_ViewPos", camera.GetPosition());
			std::dynamic_pointer_cast<Clever::OpenGLShader>(shader)->UploadUniformFloat3("u_LightPos", {0, 15, 0});
			Clever::Renderer::Submit(shader, entity.first, entity.second.size());
			counter++;
		}

		Clever::Renderer::EndScene();
	}
}