#pragma once
#include <map>
#include <vector>
#include "Platform/Object/ObjectData.h"
#include "Clever/ECS/Components/Components.h"
#include <glm/gtc/type_ptr.hpp>

namespace Clever
{

	class RenderingData
	{
	public:

		uint32_t AddObject(Ref<ObjectData> od, glm::mat4 transform, glm::vec3 texture, RigidBodyComponent rbc, PointsPositionComponent ppc);
		

		void RemoveObject(Ref<ObjectData> od, uint32_t transformIndex, uint32_t textureIndex, uint32_t rigidBoddyIndex);
		

		std::map<Ref<ObjectData>, std::vector<glm::mat4>>& getTransforms()
		{
			return transforms;
		}

		void setTransforms(std::map<Ref<ObjectData>, std::vector<glm::mat4>> t)
		{
			transforms = t;
		}

		std::map<Ref<ObjectData>, std::vector<glm::vec3>>& getTextures()
		{
			return textures;
		}

		std::map<Ref<ObjectData>, std::vector<RigidBodyComponent>>& getRigidBodies()
		{
			return rigidBodies;
		}

		void setRigidBodies(std::map<Ref<ObjectData>, std::vector<RigidBodyComponent>> r)
		{
			rigidBodies = r;
		}

		std::map<Ref<ObjectData>, std::vector<PointsPositionComponent>>& getPointPositions()
		{
			return pointPositions;
		}

		void move(Ref<ObjectData> od, uint32_t index, glm::vec3 value)
		{
			transforms.at(od).at(index) = glm::translate(transforms.at(od).at(index), value);
		}

		glm::mat4& getTransform(Ref<ObjectData> od, uint32_t index)
		{
			return transforms.at(od).at(index);
		}

		void setTransform(Ref<ObjectData> od, uint32_t index, glm::mat4 value)
		{
			transforms.at(od).at(index) = value;
		}

		glm::vec3& getTexture(Ref<ObjectData> od, uint32_t index)
		{
			return textures.at(od).at(index);
		}

		void setTexture(Ref<ObjectData> od, uint32_t index, glm::vec3 value)
		{
			textures.at(od).at(index) = value;
		}


		static RenderingData& getInstance()
		{
			static RenderingData rd;
			return rd;
		}

	private:
		RenderingData()
		{
		};

	private:
		std::map<Ref<ObjectData>, std::vector<glm::mat4>> transforms;
		std::map<Ref<ObjectData>, std::vector<glm::vec3>> textures;
		std::map<Ref<ObjectData>, std::vector<RigidBodyComponent>> rigidBodies;
		std::map<Ref<ObjectData>, std::vector<PointsPositionComponent>> pointPositions;
	};
}