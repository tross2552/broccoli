#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"

namespace brcl
{
	class BRCL_API Application
	{
	public:

		Application();

		virtual ~Application();


		void Run();

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* layer);

		void OnEvent(Event& e);

		bool OnWindowClosed(WindowClosedEvent& event);

		static inline Application& Get() { return *s_Instance; }

		inline Window& GetWindow() const { return *m_Window; }

	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;

		static Application* s_Instance;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}



