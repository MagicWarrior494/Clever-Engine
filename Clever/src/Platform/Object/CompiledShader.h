#pragma once
#include "Clever/Renderer/Shader.h"

#include <string>

namespace Clever {
	class CompiledShader {
	public:
		//For testing
		CompiledShader();

		CompiledShader(std::string vertexSrc, std::string fragmentSrc);
		~CompiledShader();
		void uploadVertexShader(std::string filePath);
		void uploadFragmentShader(std::string filePath);

		void CompileShader();

		inline Ref<Shader> getShader() const { return m_Shader; };
	private:
		std::string m_VertexSrc;
		std::string m_FragmentSrc;

		Ref<Shader> m_Shader;
	};
}