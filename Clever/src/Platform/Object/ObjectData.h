#pragma once
#include <string>
#include "Clever/Renderer/Buffer.h"
#include "Clever/Renderer/VertexArray.h"
#include "Clever/Renderer/Shader.h"
#include "CompiledShader.h"
#include <glm/glm.hpp>
namespace Clever
{

	class ObjectData
	{
	public:
		//Testing
		ObjectData();

		ObjectData(const std::string& objFilePath, CompiledShader shader);
		~ObjectData();
		inline uint32_t getVertexCount() const { return m_VertexArray->GetIndexBuffer()->GetCount(); }
		inline Ref<VertexArray> getVertexArray() const { return m_VertexArray; }
		inline CompiledShader getShader() const { return m_Shader; }

		void test();

	private:
		Ref<VertexArray> m_VertexArray;

		CompiledShader m_Shader;
	};
}