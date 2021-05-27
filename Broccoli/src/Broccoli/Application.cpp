#include "brclpch.h"
#include "Application.h"
#include "Broccoli/Events/ApplicationEvent.h"
#include "Broccoli/Log.h"
#include "Platform/Windows/WindowsWindow.h"

namespace brcl
{
	Application::Application()
	{
		m_Window = Window::Create();
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		
		WindowResizedEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			BRCL_TRACE("e is application event");
		}
		BRCL_TRACE(e);
		while (true) { m_Window->OnUpdate(); }
	}
}