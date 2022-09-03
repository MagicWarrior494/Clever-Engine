#pragma once
#include <string>
#include "Clever/Renderer/Buffer.h"
#include "Clever/Renderer/VertexArray.h"
#include "Clever/Renderer/Shader.h"
#include "CompiledShader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Platform/Object/Mesh.h>
#include <Clever/ECS/DataHandelers/RenderingData.h>
#include <glm/glm.hpp>


namespace Clever
{



	class Model
	{
	public:
		//Testing
		Model();

		Model(const std::string& objFilePath, CompiledShader shader);
		~Model();
		inline uint32_t getVertexCount() const { return m_VertexArray->GetIndexBuffer()->GetCount(); }
		inline Ref<VertexArray> getVertexArray() const { return m_VertexArray; }
		inline CompiledShader getShader() const { return m_Shader; }
		void recalculateInstancedList(std::vector<glm::mat4> transformData);
		void UpdatedColors(std::vector<glm::vec3> colorData);


	private:
		void loadModel(std::string const& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
		unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);

	private:
		std::string m_Directory;

		std::vector<Mesh> m_Meshes;

		Ref<VertexArray> m_VertexArray;
		CompiledShader m_Shader;

		uint32_t transformationsID;
		uint32_t colorsID;
	};
}