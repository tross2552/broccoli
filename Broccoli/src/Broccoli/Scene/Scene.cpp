#include "brclpch.h"
#include "Scene.h"

#include "ScriptableEntity.h"
#include "Components.h"
#include "Entity.h"
#include "Broccoli/Renderer/Renderer2D.h"

namespace brcl
{

	Entity Scene::CreateEntity(const std::string& name)
	{
		auto handle = m_Registry.create();
		Entity entity = { handle, this };

		
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();

		return entity;
		
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_EntitiesToBeRemoved.emplace_back(entity);
	}

	void Scene::OnPlay()
	{
		m_Registry.view<ScriptComponent>().each([=](entt::entity entity, ScriptComponent& script)
		{
			script.instance = script.InstantiateScript();
			script.instance->m_Entity = Entity{ entity, this };
			script.instance->OnCreate();
		});
	}

	void Scene::OnPause()
	{
		m_Registry.view<ScriptComponent>().each([=](ScriptComponent& script)
		{
			script.instance->OnDestroy();
			script.DestroyScript(&script);
		});
	}

	void Scene::OnUpdate(Timestep deltaTime)
	{

		m_Registry.view<ScriptComponent>().each([=](ScriptComponent& script)
		{
			if(script.Enabled) script.instance->OnUpdate(deltaTime);
		});
		
		//render quads
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		int i = 0;
		for(auto entity : view)
		{
			BRCL_CORE_INFO("Camera {0}: {1}", ++i, entity);
			auto& camera = view.get<CameraComponent>(entity).MyCamera;
			auto& transform = view.get<TransformComponent>(entity).MyTransform;

			renderer2d::BeginScene(camera, transform);

			m_Registry.view<ScriptComponent>().each([=](ScriptComponent& script)
			{
				if (script.Enabled) script.instance->OnRender();
			});
			

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto spriteEntity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(spriteEntity);
				
				renderer2d::DrawQuad(transform, sprite.ColorVector);
			}

			renderer2d::EndScene();
			
		}


		ClearDeletedEntities();
		
	}

	void Scene::ClearDeletedEntities()
	{
		for(auto entity : m_EntitiesToBeRemoved)
		{
			m_Registry.destroy(entity);
			
		}

		m_EntitiesToBeRemoved.clear();
	}


	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto& camera = view.get<CameraComponent>(entity).MyCamera;
			camera.ChangeAspectRatio((float)width / height);
		}
		
	}
}
