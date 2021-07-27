#pragma once
#include "Broccoli.h"

namespace brcl
{
	class EditorLayer : public Layer
	{
		friend class EditorImGuiLayer;
	public:

		EditorLayer::EditorLayer() :
			Layer("Example")
		{
		}

		~EditorLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;
		
		void OnUpdate(Timestep deltaTime) override;
		
		void OnEvent(Event& event) override;
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizedEvent& event);
		

	private:
		Entity m_ScriptDemo;
		Entity m_CameraEntity;
		std::shared_ptr<Scene> m_ActiveScene;
		
		std::shared_ptr<Texture2D> m_Texture;
		std::shared_ptr<Framebuffer> m_Framebuffer;
		
		bool m_Focused;

		float m_ZoomLevel = 2.0f;
		float m_AspectRatio;
	};

	//--------------Engine Debug Application-----------------

	struct EditorEntity
	{
		Entity Entity;
		std::string Name;
		bool Deleted;
	};
	

	//temporary app gui!!!!!
	class EditorImGuiLayer : public ImGuiLayer
	{
	public:

		EditorImGuiLayer(EditorLayer* layer) :
			ImGuiLayer("AppGuiLayer"), m_AppLayer(layer), m_isViewportFocused(false) {}

		void OnImGuiRender() override;

		void OnEvent(Event& event) override;
	
	private:

		void DrawEntityComponents(Entity entity);
		
		Entity AddEntity(std::string name);
		void ClearDeletedEntities();


	public:
		void OnAttach() override;
	private:

		EditorLayer* m_AppLayer;
		bool m_isViewportFocused;

		Entity m_Selection;

		std::vector<EditorEntity> m_SceneEntities;
		int m_EntityCount;
	};
}
