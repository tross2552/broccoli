#pragma once
#include "Broccoli.h"

namespace brcl
{
	class EditorLayer : public Layer
	{
		friend class EditorImGuiLayer;
	public:

		EditorLayer::EditorLayer() :
			Layer("Example"), m_CameraController(16.0f / 9.0f), m_Color(nullptr), m_TexParams({0.0f, 0.0f, 2.0f, 8.0f}) {}
		~EditorLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;
		
		void OnUpdate(Timestep deltaTime) override;
		void OnEvent(Event& event) override;

	private:
		CameraController m_CameraController;
		std::shared_ptr<Scene> m_ActiveScene;
		
		std::shared_ptr<Texture2D> m_Texture;
		std::shared_ptr<Framebuffer> m_Framebuffer;

		Vector4* m_Color;
		Vector4 m_TexParams;
		bool m_Focused;
	};

	//--------------Engine Debug Application-----------------

	//temporary app gui!!!!!
	class EditorImGuiLayer : public ImGuiLayer
	{
	public:

		EditorImGuiLayer(EditorLayer* layer) :
			ImGuiLayer("AppGuiLayer"), m_AppLayer(layer), m_isViewportFocused(false) {}

		void OnImGuiRender() override;

		void OnEvent(Event& event) override;

	private:

		EditorLayer* m_AppLayer;
		bool m_isViewportFocused;
	};
}
