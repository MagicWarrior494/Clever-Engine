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
		inline uint32_t getVerticesSize() const { return sizeof(m_Vertices); }
		inline uint32_t getIndiciesSize() const { return sizeof(m_Indicies); }
	private:
		uint32_t Vertsize = 3644;
		uint32_t Indsize = 6320;
		float* m_Vertices = new float[Vertsize];
		uint32_t* m_Indicies = new uint32_t[Indsize];
	};
}