#pragma once
#include "Broccoli.h"

namespace Sandbox
{
	class SandboxLayer : public brcl::Layer
	{
		friend class ExampleImGuiLayer;
	public:

		SandboxLayer::SandboxLayer() :
			Layer("Example"), m_CameraController(16.0f / 9.0f), m_Color(1.0f), m_TexParams({0.0f, 0.0f, 2.0f, 8.0f}) {}
		~SandboxLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;
		
		void OnUpdate(brcl::Timestep deltaTime) override;
		bool OnResize(brcl::WindowResizedEvent& event);
		void OnEvent(brcl::Event& event) override;

	private:
		brcl::CameraController m_CameraController;
		brcl::Vector4 m_Color;
		brcl::Vector4 m_TexParams;
		std::shared_ptr<brcl::Texture2D> m_Texture;
		std::shared_ptr<brcl::Framebuffer> m_Framebuffer;
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

		ExampleImGuiLayer(SandboxLayer* layer) :
			ImGuiLayer("AppGuiLayer"), m_AppLayer(layer)
		{
		}

		void OnImGuiRender() override;

		void OnEvent(brcl::Event& event) override;

	private:

		SandboxLayer* m_AppLayer;
	};
}
