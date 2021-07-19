#pragma once
#include <entt.hpp>
#include "Components.h"
namespace brcl
{

	class Entity;
	
	class Scene
	{

		friend class Entity;
		
	public:
		Scene();
		~Scene() = default;

		Entity CreateEntity(const std::string& name);
		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;
	};

	
	
}
