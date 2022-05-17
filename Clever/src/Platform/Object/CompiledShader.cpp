#include "cvpch.h"
#include "CompiledShader.h"
#include <iostream>
#include <fstream>

namespace Clever {
	CompiledShader::CompiledShader()
	{
	}
	CompiledShader::CompiledShader(std::string vertexSrc, std::string fragmentSrc)
	{
		uploadVertexShader(vertexSrc);
		uploadFragmentShader(fragmentSrc);
		CompileShader();
	}

	CompiledShader::~CompiledShader()
	{
	}

	void CompiledShader::uploadVertexShader(std::string filePath)
	{
		std::string vertexString = "";
		std::ifstream file;
		file.open(filePath);

		std::string line;

		if (file.is_open())
		{
			while (std::getline(file, line)) {
				vertexString.append(line + "\n");
			}
			file.close();
		}
		else CV_CORE_ERROR("VERTEX SHADER FILE COULD NOT BE OPENED: {0}", filePath);

		m_VertexSrc = vertexString;
	}
	void CompiledShader::uploadFragmentShader(std::string filePath)
	{
		std::string fragmentString = "";
		std::ifstream file;
		file.open(filePath);

		std::string line;

		if (file.is_open())
		{
			while (std::getline(file, line)) {
				fragmentString.append(line + "\n");
			}
			file.close();
		}
		else CV_CORE_ERROR("VERTEX SHADER FILE COULD NOT BE OPENED: {0}", filePath);

		m_FragmentSrc = fragmentString;
	}

	void CompiledShader::CompileShader()
	{
		m_Shader.reset(Shader::Create(m_VertexSrc, m_FragmentSrc));
	}
}