#pragma once
#include "Components.h"
#include "Broccoli/Scene/Entity.h"
#include "Broccoli/Core/Timer.h"
namespace brcl
{

	class ScriptableEntity;

	struct ScriptComponent
	{
		ScriptableEntity* instance;
		bool m_Enabled;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(ScriptComponent*);

		template <typename T>
		void Bind()
		{
			InstantiateScript = []()
			{
				return static_cast<ScriptableEntity*>(new T());
			};
			DestroyScript = [](ScriptComponent* component)
			{
				delete component->instance;
				component->instance = nullptr;
			};
		}
	};
	
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
