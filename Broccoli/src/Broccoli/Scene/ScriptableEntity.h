#pragma once
#include "Broccoli/Scene/Entity.h"
#include "Broccoli/Core/Timer.h"
namespace brcl
{
	class ScriptableEntity
	{

		friend class Scene;
		
	public:
		virtual ~ScriptableEntity() = default;

		template <typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
		
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}
	
	private:
		Entity m_Entity;
		
	};

}
