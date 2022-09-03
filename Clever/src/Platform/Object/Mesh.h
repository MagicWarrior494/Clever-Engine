#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Platform/Object/CompiledShader.h>
#include "Clever/Renderer/VertexArray.h"

#include <string>
#include <vector>

    
namespace Clever
{

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh 
    {
    public:
        // Constructor
        Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        
    private:
        // Mesh Data
        Ref<VertexArray> m_VertexArray;
        Ref<IndexBuffer> indexBuffer;
        std::vector<Texture> textures;
    };
 }