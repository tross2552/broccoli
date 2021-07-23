#include "brclpch.h"
#include "SceneSerializer.h"

#include "yaml-cpp/yaml.h"
#include <filesystem>
#include <fstream>

#include "Entity.h"

namespace YAML
{
	template<>
	struct convert<brcl::Vector3>
	{
		static Node encode(const brcl::Vector3& rhs)
		{
			Node node;
			node.push_back(rhs[0]);
			node.push_back(rhs[1]);
			node.push_back(rhs[2]);
			return node;
		}

		static bool decode(const Node& node, brcl::Vector3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs[0] = node[0].as<float>();
			rhs[1] = node[1].as<float>();
			rhs[2] = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<brcl::Vector4>
	{
		static Node encode(const brcl::Vector4& rhs)
		{
			Node node;
			node.push_back(rhs[0]);
			node.push_back(rhs[1]);
			node.push_back(rhs[2]);
			node.push_back(rhs[3]);
			return node;
		}

		static bool decode(const Node& node, brcl::Vector4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs[0] = node[0].as<float>();
			rhs[1] = node[1].as<float>();
			rhs[2] = node[2].as<float>();
			rhs[3] = node[3].as<float>();
			return true;
		}
	};

}

namespace brcl
{

	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		if (entity.GetComponent<TagComponent>().Tag == "Editor Camera") return;
		
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << "insert HUD here";
		
		if(entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			
			out << YAML::Key << "TagComponent" << YAML::BeginMap;
			out << YAML::Key << "Tag" << YAML::Value << tag;
			out << YAML::EndMap;
		}

		if(entity.HasComponent<TransformComponent>())
		{
			auto& transform = entity.GetComponent<TransformComponent>().MyTransform;

			Vector3 pos = transform.GetPosition();
			Vector3 rot = transform.GetRotation();
			Vector3 scl = transform.GetScale();
			
			out << YAML::Key << "TransformComponent" << YAML::BeginMap;
			out << YAML::Key << "Position" << YAML::Value;
			out << YAML::Flow << YAML::BeginSeq << pos[0] << pos[1] << pos[2] << YAML::EndSeq;
			out << YAML::Key << "Rotation" << YAML::Value;
			out << YAML::Flow << YAML::BeginSeq << rot[0] << rot[1] << rot[2] << YAML::EndSeq;
			out << YAML::Key << "Scale" << YAML::Value;
			out << YAML::Flow << YAML::BeginSeq << scl[0] << scl[1] << scl[2] << YAML::EndSeq;
			out << YAML::EndMap;
		}

		if(entity.HasComponent<SpriteRendererComponent>())
		{
			auto& renderer = entity.GetComponent<SpriteRendererComponent>();

			Vector4 color = renderer.ColorVector;
			Vector4 texTransform = renderer.TextureTransform;

			out << YAML::Key << "SpriteRendererComponent" << YAML::BeginMap;
			out << YAML::Key << "Color" << YAML::Value;
			out << YAML::Flow << YAML::BeginSeq << color[0] << color[1] << color[2] << color[3] << YAML::EndSeq;
			out << YAML::Key << "Texture Transform" << YAML::Value;
			out << YAML::Flow << YAML::BeginSeq << texTransform[0] << texTransform[1] << texTransform[2] << texTransform[3] << YAML::EndSeq;
			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}
	
	void SceneSerializer::Serialize(const std::string& path)
	{
		
		std::filesystem::path filepath = path;
		BRCL_CORE_ASSERT(std::filesystem::exists(filepath.parent_path()), "Serialization error: scene directory does not exist!"); //for dev purposes, avoid creating new directories (this check could get annoying)
		std::string sceneName = filepath.stem().string();

		BRCL_CORE_TRACE("Serializing scene {0}", sceneName);

		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Key << sceneName;
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		
		m_Scene->m_Registry.each([&](auto& entityID)
		{

			Entity entity = { entityID, m_Scene.get() };
			if (!entity) return;

			SerializeEntity(out, entity);

		});

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
		
	}

	bool SceneSerializer::Deserialize(const std::string& path)
	{
		std::filesystem::path filepath = path;
		BRCL_CORE_ASSERT(std::filesystem::exists(filepath), "Deserialization error: scene path does not exist!");
		std::string name = filepath.stem().string();

		std::ifstream stream(filepath);
		std::stringstream strstream;
		strstream << stream.rdbuf();
		YAML::Node data = YAML::Load(strstream.str());
		if (!data["Scene"]) return false;
		std::string sceneName = data["Scene"].as<std::string>();
		BRCL_CORE_TRACE("Deserializing scene {0}", sceneName);

		if (auto entities = data["Entities"]; entities)
		{
			for(auto entity : entities)
			{
				Entity deserialized;

				if (auto tagData = entity["TagComponent"]; tagData)
				{
					auto tag = tagData["Tag"].as<std::string>();
					deserialized = m_Scene->CreateEntity(name);
				}
				else
				{
					BRCL_CORE_WARN("Deserialization error: entity does not have tag component!");
					continue;
				}
				
				if (auto transformData = entity["TransformComponent"]; transformData)
				{
					
					auto& transform = deserialized.GetComponent<TransformComponent>();
					transform.MyTransform.SetPosition(transformData["Position"].as<Vector3>());
					transform.MyTransform.SetRotation(transformData["Rotation"].as<Vector3>());
					transform.MyTransform.SetScale(transformData["Scale"].as<Vector3>());

				}
				if(auto rendererData = entity["SpriteRendererComponent"]; rendererData)
				{
					auto& renderer = deserialized.AddComponent<SpriteRendererComponent>();
					renderer.ColorVector = rendererData["Color"].as<Vector4>();
					renderer.TextureTransform = rendererData["Texture Transform"].as<Vector4>();
				}
			}
		}
		return true;
	}

}
