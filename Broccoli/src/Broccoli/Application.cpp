#include "brclpch.h"
#include "Application.h"
#include "Broccoli/Events/ApplicationEvent.h"
#include "Broccoli/Log.h"

namespace brcl
{
	Application::Application()
	{
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
		while (true);
	}
}