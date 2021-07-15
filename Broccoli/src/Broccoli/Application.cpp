#include "brclpch.h"
#include "Application.h"
#include "Broccoli/Core/Core.h"
#include "Broccoli/Events/ApplicationEvent.h"
#include "Broccoli/Renderer/Renderer.h"
#include "Broccoli/Renderer/Renderer2D.h"

namespace brcl
{

	Application* Application::s_Instance = nullptr;

	Application::Application(std::string name) :
		m_Timer("Application"), m_Minimized(false)
	{
		if (!s_Instance) s_Instance = this;
		else return;

		m_Window = std::unique_ptr<Window>(Window::Create({name}));
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
					BRCL_INFO("Updating layer {0}", layer->GetName());
					layer->OnUpdate(deltaTime);
				}
			}

			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false;
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

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			BRCL_INFO("Sending Event {0} to layer {1}", event, (*it)->GetName());
			(*it)->OnEvent(event);
			if (event.GetHandled()) break;
		}

	}

	bool Application::OnWindowClosed(WindowClosedEvent& event)
	{
		Close();
		return false;
	}

	bool Application::OnWindowResized(WindowResizedEvent& event)
	{
		m_Minimized = event.GetWidth() == 0 && event.GetHeight() == 0;
		return false;
	}
}