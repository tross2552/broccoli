#pragma once
#include "Broccoli.h"

namespace Sandbox
{
	class Sandbox2DLayer : public brcl::Layer
	{
		friend class ExampleImGuiLayer;
	public:

		Sandbox2DLayer::Sandbox2DLayer() :
			Layer("Example"), m_CameraController(16.0f / 9.0f), m_Color(1.0f) {}
		~Sandbox2DLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;
		
		void OnUpdate(brcl::Timestep deltaTime) override;
		void OnEvent(brcl::Event& event) override;

	private:
		brcl::CameraController m_CameraController;
		brcl::Vector4 m_Color;
		std::shared_ptr<brcl::Texture2D> m_Texture;


	};

	//--------------Engine Debug Application-----------------
	
	class ExampleLayer : public brcl::Layer
	{

		friend class ExampleImGuiLayer;
		
	public:
		ExampleLayer();

		void OnUpdate(brcl::Timestep deltaTime) override;

		void OnEvent(brcl::Event& event) override;

	private:

		brcl::ShaderLibrary m_ShaderLibrary;
		std::shared_ptr<brcl::VertexArray> m_VertexArray;
		std::shared_ptr<brcl::VertexArray> m_VertexArraySquare;
		std::shared_ptr<brcl::Texture2D> m_Texture;
		std::shared_ptr<brcl::Texture2D> m_TextureLogo;
		brcl::Vector4 m_Color;

		brcl::CameraController m_CameraController;
		
	};

	//temporary app gui!!!!!
	class ExampleImGuiLayer : public brcl::ImGuiLayer
	{
	public:

		ExampleImGuiLayer(Sandbox2DLayer* layer) :
			ImGuiLayer("AppGuiLayer"), m_AppLayer(layer)
		{
		}

		void OnImGuiRender() override;

	private:

		Sandbox2DLayer* m_AppLayer;
	};
}
