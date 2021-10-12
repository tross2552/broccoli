#pragma once
#include <entt.hpp>

#include "Broccoli/Math/Math.h"

namespace brcl
{

	class Entity;
	
	class Scene
	{

		friend class Entity;
		friend class SceneSerializer;
		friend class EditorImGuiLayer;
		
	public:
		Scene();
		~Scene() = default;

		static Scene* GetActiveScene() //todo: scene manager
		{
			return s_ActiveScene;
		}

		Entity CreateEntity(const std::string& name);
		void DestroyEntity(Entity entity);

		void SetTransform(entt::entity handle, Vector3 position);

		void OnPlay();
		void OnPause();
		void OnUpdate(Timestep deltaTime);

		void OnViewportResize(uint32_t width, uint32_t height);
	
	private:
		void ClearDeletedEntities();
	
	private:
		entt::registry m_Registry;

		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		std::vector<entt::entity> m_EntitiesToBeRemoved;

		static Scene* s_ActiveScene;
	};

	
	
}
