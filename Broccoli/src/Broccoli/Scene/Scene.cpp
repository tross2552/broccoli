#include "brclpch.h"
#include "Scene.h"

#include "Components.h"
#include "Entity.h"
#include "Broccoli/Renderer/Renderer2D.h"

namespace brcl
{

	static void DoMath(const Matrix4x4& transform)
	{
		
	}
	
	Scene::Scene()
	{
#if 0
		Entity oneEntity = m_Registry.create();

		m_Registry.emplace<TransformComponent>(oneEntity, Identity4x4());
		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

		if (m_Registry.any_of<TransformComponent>(oneEntity)) TransformComponent& transform = m_Registry.get<TransformComponent>(oneEntity);

		
		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
			TransformComponent& transform = view.get<TransformComponent>(entity);

		
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for( auto entity : group)
			auto& [transform, mesh] = group.get<TransformComponent, SpriteRendererComponent>(entity);
#endif	
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		auto handle = m_Registry.create();
		Entity entity = { handle, this };

		
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();

		return entity;
		
	}

	void Scene::OnUpdate(Timestep ts)
	{

		//render quads
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		int i = 0;
		for(auto entity : view)
		{
			BRCL_CORE_INFO("Camera {0}: {1}", ++i, entity);
			auto& camera = view.get<CameraComponent>(entity).MyCamera;
			auto& transform = view.get<TransformComponent>(entity).MyTransform;

			renderer2d::BeginScene(camera, transform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto spriteEntity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(spriteEntity);
				renderer2d::DrawQuad(transform, sprite.ColorVector);
			}

			renderer2d::EndScene();
			
		}
	}

	
}