#include "cvpch.h"
#include "Mesh.h"

namespace Clever
{
	Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    {
        m_VertexArray.reset(Clever::VertexArray::Create());

        Clever::Ref<Clever::VertexBuffer> vertexBuffer;
        Clever::Ref<Clever::IndexBuffer> indexBuffer;

        vertexBuffer.reset(Clever::VertexBuffer::Create(vertices, vertices.size() * sizeof(float)));

        Clever::BufferLayout layout = {
           { Clever::ShaderDataType::Float3, "a_Position" },
           { Clever::ShaderDataType::Float3, "a_Normal" }
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        indexBuffer.reset(Clever::IndexBuffer::Create(indices, indices.size()));
        m_VertexArray->SetIndexBuffer(indexBuffer);
    }
}