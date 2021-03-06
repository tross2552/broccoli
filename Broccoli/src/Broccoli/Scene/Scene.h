#pragma once
#include <entt.hpp>

namespace brcl
{

	class Entity;
	
	class Scene
	{

		friend class Entity;
		friend class SceneSerializer;
		friend class EditorImGuiLayer;
		
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string& name);
		void DestroyEntity(Entity entity);

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
	};

	
	
}
