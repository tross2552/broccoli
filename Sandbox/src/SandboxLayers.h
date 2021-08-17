#pragma once
#include "Broccoli.h"

namespace Sandbox
{
	class SandboxLayer : public brcl::Layer
	{
		friend class ExampleImGuiLayer;
	public:

		SandboxLayer::SandboxLayer() :
			Layer("Example") {}
		~SandboxLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;
		
		void OnUpdate(brcl::Timestep deltaTime) override;
		bool OnResize(brcl::WindowResizedEvent& event);
		void OnEvent(brcl::Event& event) override;

	private:
		std::shared_ptr<brcl::Framebuffer> m_Framebuffer;
		std::unique_ptr<brcl::AudioDevice> m_audioDevice = brcl::AudioDevice::Create();
		std::unique_ptr<brcl::AudioSource> m_audioSource = brcl::AudioSource::Create();

		std::shared_ptr<brcl::Scene> m_Scene;
		brcl::Entity m_Player;
		brcl::Entity m_Level;

		float m_ZoomLevel = 10.0f;
		float m_AspectRatio;
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
