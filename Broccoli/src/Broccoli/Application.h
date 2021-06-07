#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

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

	private:

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}



