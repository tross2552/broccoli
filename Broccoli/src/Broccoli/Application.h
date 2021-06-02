#pragma once

#include "Core.h"
#include "Window.h"

namespace brcl
{
	class BRCL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		bool OnWindowClosed(WindowClosedEvent& event);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}



