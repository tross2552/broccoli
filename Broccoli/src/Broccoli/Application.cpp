#include "brclpch.h"
#include "Application.h"
#include "Broccoli/Core/Core.h"
#include "Broccoli/Events/ApplicationEvent.h"
#include "Broccoli/Renderer/Renderer.h"

namespace brcl
{

	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_Timer("Application")
	{
		if (!s_Instance) s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		Renderer::Init();
		
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
			
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(deltaTime);
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
		BRCL_CORE_TRACE(event.ToString());

		for (auto& layer : m_LayerStack)
		{
			layer->OnEvent(event);
			if (event.GetHandled()) break;
		}

	}

	bool Application::OnWindowClosed(WindowClosedEvent& e)
	{
		m_Running = false;
		return true;
	}
}