#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

namespace brcl
{
	class BRCL_API Application
	{
	public:

		Application(std::string name = "Broccoli Application");
		virtual ~Application();

		void Run();
		void Close();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void OnEvent(Event& e);

		bool OnWindowClosed(WindowClosedEvent& event);
		bool OnWindowResized(WindowResizedEvent& event);

		static Application& Get() { return *s_Instance; }

		Window& GetWindow() const { return *m_Window; }

	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
		bool m_Minimized;

		static Application* s_Instance;

		Timer m_Timer;
		Timestep m_PrevTime;
		
		
	};

	//To be defined in CLIENT
	extern Application* CreateApplication();

}



