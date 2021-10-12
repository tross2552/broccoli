#pragma once
#include "Broccoli.h"

namespace Sandbox
{
	class Player : public brcl::ScriptableEntity
	{
	public:

		void OnCreate() override
		{
			auto& transform = GetComponent<brcl::TransformComponent>().MyTransform;
			transform.SetPosition({ 0.5f,0.5f,0.0f });
			
		}

		void OnUpdate(brcl::Timestep deltaTime) override
		{
			auto& rb = GetComponent<brcl::RigidBodyComponent>();
			constexpr float speed = 2.0f;

			if (brcl::Input::IsKeyPressed(brcl::Input::KeyCode::W))
				rb.SetVelocity(GetHandle(), { 0.0f, speed });

			else if (brcl::Input::IsKeyPressed(brcl::Input::KeyCode::A))
				rb.SetVelocity(GetHandle(), { -speed, 0.0f });

			else if (brcl::Input::IsKeyPressed(brcl::Input::KeyCode::S))
				rb.SetVelocity(GetHandle(), { 0.0f, -speed });

			else if (brcl::Input::IsKeyPressed(brcl::Input::KeyCode::D))
				rb.SetVelocity(GetHandle(), { speed, 0.0f });

			else
				rb.SetVelocity(GetHandle(), { 0.0f,0.0f });
			
			if (brcl::Input::IsKeyPressed(brcl::Input::KeyCode::X))
			{
				GetComponent<brcl::TransformComponent>().MyTransform.SetPosition({ 0.5f, 4.0f, 0.0f });
			}
		}
	};

	

	class Level : public brcl::ScriptableEntity
	{

		std::shared_ptr<brcl::Texture2D> m_TextureSky;
		std::shared_ptr<brcl::Texture2D> m_Texture0;
		std::shared_ptr<brcl::Texture2D> m_Texture1;
		std::shared_ptr<brcl::Texture2D> m_Texture2;
		

		void OnCreate() override
		{
			m_TextureSky = brcl::Texture2D::Create("assets/textures/Magic-Cliffs-Environment/levelsky.png");
			m_Texture2 = brcl::Texture2D::Create("assets/textures/Magic-Cliffs-Environment/level2.png");
			m_Texture1 = brcl::Texture2D::Create("assets/textures/Magic-Cliffs-Environment/level1.png");
			m_Texture0 = brcl::Texture2D::Create("assets/textures/Magic-Cliffs-Environment/level0.png");
		}
		
		void OnRender() override
		{
			
			brcl::Transform transform;
			transform.SetScale({ 8.0f, 4.0f, 1.0f });
			transform.SetPosition({ -1.0f, -0.5f, 0.8f });
			brcl::renderer2d::DrawQuad(transform, m_TextureSky);

			transform.SetScale({ 6.0f, 3.0f, 1.0f });
			transform.SetPosition({ 0.1f, 0.0f, 0.4f });
			brcl::renderer2d::DrawQuad(transform, m_Texture2);

			transform.SetScale({ 6.0f, 3.0f, 1.0f });
			transform.SetPosition({ 0.0f, 0.0f, 0.0f });
			brcl::renderer2d::DrawQuad(transform, m_Texture1);

			transform.SetScale({ 6.0f, 3.0f, 1.0f });
			transform.SetPosition({ 0.0f, -0.1f, -0.3f });
			brcl::renderer2d::DrawQuad(transform, m_Texture0);
		}
	};
}