#include "cvpch.h"
#include "GameObject.h"
#include <fstream>

namespace Clever
{
	GameObject::GameObject(const std::string& objFilePath)
	{
		std::string line;
		std::ifstream file(objFilePath);
		std::string space_delimiter = " ";

		std::vector<float> vertices;
		std::vector<uint32_t> indicies;

		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				std::vector<std::string> words{};

				size_t pos = 0;
				while ((pos = line.find(space_delimiter)) != std::string::npos) {
					words.push_back(line.substr(0, pos));
					line.erase(0, pos + space_delimiter.length());
				}
				std::stringstream s_stream(line);

				while (s_stream.good()) {
					std::string substr;
					getline(s_stream, substr, ' '); //get first string delimited by comma
					words.push_back(substr);
				}

				/*for (std::string s : words)
				{
					CV_CORE_TRACE("words: {0}", s);
				}*/
				
				if (words.size() == 4)
				{
					if (words.at(0) == "v")
					{
						vertices.push_back(std::stof(words.at(1)));
						vertices.push_back(std::stof(words.at(2)));
						vertices.push_back(std::stof(words.at(3)));
					}
					else if (words.at(0) == "f")
					{
						indicies.push_back(std::stof(words.at(1)) - 1);
						indicies.push_back(std::stof(words.at(2)) - 1);
						indicies.push_back(std::stof(words.at(3)) - 1);
					}
				}
			}
			file.close();
		}
		else
		{
			CV_CORE_ERROR("COULD OPEN FILE: {0}", objFilePath);
		}

		/*CV_CORE_TRACE("vertices: {0}", vertices.size());
		CV_CORE_TRACE("indicies: {0}", indicies.size());*/

		std::copy(vertices.begin(), vertices.end(), m_Vertices);
		std::copy(indicies.begin(), indicies.end(), m_Indicies);

	}
	GameObject::~GameObject()
	{
		delete[] m_Indicies;
		delete[] m_Vertices;
	}
}
