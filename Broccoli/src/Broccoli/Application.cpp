#include "brclpch.h"
#include "Application.h"
#include "Broccoli/Core/Core.h"
#include "Broccoli/Events/ApplicationEvent.h"
#include "Broccoli/Renderer/Renderer.h"
#include "Broccoli/Renderer/Renderer2D.h"

namespace brcl
{

	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_Timer("Application"), m_Minimized(false)
	{
		if (!s_Instance) s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		renderer::Init();
		renderer2d::Init();
		
	}
	Application::~Application()
	{

	}

	void Application::Run()
	{
		
		while (m_Running) {

			Timestep curr = m_Timer.GetTime();

			Timestep deltaTime = curr - m_PrevTime;
			m_PrevTime = curr;

			if (!m_Minimized)
			{

				for (Layer* layer : m_LayerStack)
				{

					layer->OnUpdate(deltaTime);
				}
			}

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowClosedEvent>(BRCL_BIND_EVENT_FN(Application::OnWindowClosed) );
		dispatcher.Dispatch<WindowResizedEvent>(BRCL_BIND_EVENT_FN(Application::OnWindowResized));
		BRCL_CORE_TRACE(event.ToString());

		for (auto& layer : m_LayerStack)
		{
			layer->OnEvent(event);
			if (event.GetHandled()) break;
		}

	}

	bool Application::OnWindowClosed(WindowClosedEvent& event)
	{
		m_Running = false;
		return false;
	}

	bool Application::OnWindowResized(WindowResizedEvent& event)
	{
		m_Minimized = event.GetWidth() == 0 && event.GetHeight() == 0;
		renderer::ResizeViewport(event.GetWidth(), event.GetHeight());
		return false;
	}
}