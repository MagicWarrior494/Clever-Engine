#include "cvpch.h"
#include "ObjectData.h"
#include <fstream>

namespace Clever
{
	ObjectData::ObjectData()
	{
	}

	ObjectData::ObjectData(const std::string& objFilePath, CompiledShader shader)
		: m_Shader(shader)
	{
		
		std::string line;
		std::ifstream file(objFilePath);
		std::string space_delimiter = " ";

		std::vector< std::vector<float>> vertices;
		std::vector< std::vector<float>> normals;
		std::vector<std::vector<float>> data{};

		std::vector<float> finalVertices;
		std::vector<uint32_t> finalIndicies;

		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				std::vector<std::string> words{};
				std::stringstream s_stream(line);

				while (s_stream.good()) {
					std::string substr;
					getline(s_stream, substr, ' '); //get first string delimited by comma
					words.push_back(substr);
				}

				if (words.size() == 4)
				{
					if (words.at(0) == "v")
					{
						vertices.push_back({ std::stof(words.at(1)), std::stof(words.at(2)), std::stof(words.at(3)) });
					}
					else if (words.at(0) == "vn")
					{
						normals.push_back({ std::stof(words.at(1)), std::stof(words.at(2)), std::stof(words.at(3)) });
					}
					else if (words.at(0) == "f")
					{
						uint32_t faceIndex[3];
						
						for (int i = 0; i < 3; i++)
						{
							std::vector<std::string> values{};

							std::string value = words.at(i + 1);
							values.push_back(value.substr(0, value.find("//")));
							values.push_back(value.substr(value.find("//") + 2, value.size()));
							std::vector<float> v = vertices.at(std::stoi(values.at(0)) - 1);
							std::vector<float> n = normals.at(std::stoi(values.at(1)) - 1);
							std::vector<float> temp_data{ v.at(0), v.at(1), v.at(2), n.at(0), n.at(1), n.at(2) };

							bool good = true;
							if (vertices.size() != normals.size())
							{
								for (int j = 0; j < data.size(); j++)
								{
									if (data.at(j) == temp_data)
									{
										good = false;
										faceIndex[i] = j;
										break;
									}
								}
							}
							if (good)
							{
								faceIndex[i] = data.size();
								data.push_back(temp_data);
							}
						}
						for (uint32_t item : faceIndex)
						{
							finalIndicies.push_back(item);
						}
					}
				}
			}
			file.close();
		}
		else
		{
			CV_CORE_ERROR("COULD OPEN FILE: {0}", objFilePath);
		}

		for (std::vector item : data)
			for (float f : item)
				finalVertices.push_back(f);

		m_VertexArray.reset(Clever::VertexArray::Create());

		Clever::Ref<Clever::VertexBuffer> vertexBuffer;
		Clever::Ref<Clever::IndexBuffer> indexBuffer;

		vertexBuffer.reset(Clever::VertexBuffer::Create(finalVertices, finalVertices.size() * sizeof(float)));

		//teapot.test();

		Clever::BufferLayout layout = {
			{ Clever::ShaderDataType::Float3, "a_Position" },
			{ Clever::ShaderDataType::Float3, "a_Normal" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		indexBuffer.reset(Clever::IndexBuffer::Create(finalIndicies, finalIndicies.size()));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		data.clear();
		vertices.clear();
		normals.clear();
	}
	ObjectData::~ObjectData()
	{

	}
	void ObjectData::test()
	{
		
	}
}
