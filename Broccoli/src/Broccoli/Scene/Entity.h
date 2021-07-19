#pragma once
#include <entt.hpp>

#include "Scene.h"

namespace brcl
{
	class Entity
	{
	public:

		Entity() :
			m_Scene(nullptr), m_Handle(entt::null) {}

		Entity(entt::entity entity, Scene* scene) :
			m_Scene(scene), m_Handle(entity) {}
		
		~Entity() = default;

		template <typename T, typename... Args>
		T& AddComponent(Args &&... args)
		{
			return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
		}

		template <typename T>
		T* GetComponent()
		{
			return m_Scene->m_Registry.try_get<T>(m_Handle);
		}

		template <typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_Handle);
		}

		template <typename T>
		void RemoveComponent()
		{
			m_Scene->m_Registry.remove_if_exists<T>(m_Handle);
		}

		operator bool() const { return m_Handle != entt::null; }
	
	private:
		Scene* m_Scene;
		entt::entity m_Handle;
	};
}
