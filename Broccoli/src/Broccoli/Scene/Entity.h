#pragma once
#include <entt.hpp>

#include "Components.h"
#include "Broccoli/Scene/Scene.h"

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
			BRCL_CORE_ASSERT(m_Scene->m_Registry.valid(m_Handle), "Scene error: Entity not valid!");
			BRCL_CORE_ASSERT(!m_Scene->m_Registry.any_of<T>(m_Handle), "Scene error: Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
		}

		template <typename T>
		T& GetComponent()
		{
			BRCL_CORE_ASSERT(m_Scene->m_Registry.valid(m_Handle), "Scene error: Entity not valid!");
			BRCL_CORE_ASSERT(m_Scene->m_Registry.all_of<T>(m_Handle), "Scene error: Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_Handle);
		}

		template <typename T>
		bool HasComponent()
		{
			BRCL_CORE_ASSERT(m_Scene->m_Registry.valid(m_Handle), "Scene error: Entity not valid!");
			return m_Scene->m_Registry.any_of<T>(m_Handle);
		}

		template <typename T>
		void RemoveComponent()
		{
			BRCL_CORE_ASSERT(m_Scene->m_Registry.valid(m_Handle), "Scene error: Entity not valid!");
			BRCL_CORE_ASSERT(m_Scene->m_Registry.all_of<T>(m_Handle), "Scene error: Entity does not have component!");
			m_Scene->m_Registry.remove_if_exists<T>(m_Handle);
		}

		operator bool() const { return m_Handle != entt::null; }

		bool operator==(const Entity& other) const
		{
			return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

		operator entt::entity() const
		{
			return m_Handle;
		}

		operator std::string() const
		{
			return std::to_string(((uint32_t)m_Handle));
		}
	
	private:
		Scene* m_Scene;
		entt::entity m_Handle;
	};
}
