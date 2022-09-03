#include "cvpch.h"
#include "RenderingData.h"

namespace Clever {

	uint32_t RenderingData::AddObject(Ref<ObjectData> od, glm::mat4 transform, glm::vec3 texture, RigidBodyComponent rbc, PointsPositionComponent ppc)
	{
		if (transforms.find(od) == transforms.end())
			transforms.insert({ od, {} });
		if (textures.find(od) == textures.end())
			textures.insert({ od, {} });
		if (rigidBodies.find(od) == rigidBodies.end())
			rigidBodies.insert({ od, {} });
		if (pointPositions.find(od) == pointPositions.end())
			pointPositions.insert({ od, {} });


		transforms.at(od).push_back(transform);
		textures.at(od).push_back(texture);
		rigidBodies.at(od).push_back(rbc);
		pointPositions.at(od).push_back(ppc);

		return transforms.at(od).size() - 1;
	}

	void RenderingData::RemoveObject(Ref<ObjectData> od, uint32_t transformIndex, uint32_t textureIndex, uint32_t rigidBodyIndex)
	{
		transforms.at(od).erase(transforms.at(od).begin() + transformIndex);
		textures.at(od).erase(textures.at(od).begin() + textureIndex);
		rigidBodies.at(od).erase(rigidBodies.at(od).begin() + rigidBodyIndex);
	}

}