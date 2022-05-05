#pragma once
#include <string>

namespace Clever
{

	class GameObject
	{
	public:
		GameObject(const std::string& objFilePath);
		~GameObject();
		inline float* getVertices() const { return m_Vertices; }
		inline uint32_t* getIndicies() const { return m_Indicies; }
		inline uint32_t getVerticesSize() const { return Vertsize * 4; }
		inline uint32_t getIndiciesSize() const { return Indsize * 4; }
	private:
		uint32_t Vertsize;
		uint32_t Indsize;
		float* m_Vertices = new float[Vertsize];
		uint32_t* m_Indicies = new uint32_t[Indsize];
	};
}