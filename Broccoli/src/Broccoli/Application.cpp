#include "brclpch.h"
#include "Application.h"
#include "Broccoli/Events/ApplicationEvent.h"
#include "Broccoli/Log.h"
#include "Platform/Windows/WindowsWindow.h"

#include <GLFW/glfw3.h>

namespace brcl
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		
		while (m_Running) { m_Window->OnUpdate(); }
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowClosedEvent>(std::bind(&Application::OnWindowClosed, this, std::placeholders::_1));
		BRCL_CORE_TRACE(event.ToString());
	}

	bool Application::OnWindowClosed(WindowClosedEvent& e)
	{
		m_Running = false;
		return true;
	}
}