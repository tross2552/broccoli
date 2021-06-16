#include "brclpch.h"
#include "Application.h"
#include "Broccoli/Events/ApplicationEvent.h"
#include "Broccoli/Log.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Windows/WindowsInput.h"

#include <glad/glad.h>

namespace brcl
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		if (!s_Instance) s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, & m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		const float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		const unsigned int indices [] = { 0 , 1 , 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
	Application::~Application()
	{

	}

	void Application::Run()
	{
		
		while (m_Running) { 

			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it)
			{
				(*it)->OnUpdate();
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
		dispatcher.Dispatch<WindowClosedEvent>(std::bind(&Application::OnWindowClosed, this, std::placeholders::_1));
		BRCL_CORE_TRACE(event.ToString());

		for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it)
		{
			(*it)->OnEvent(event);
			if (event.GetHandled()) break;
		}

	}

	bool Application::OnWindowClosed(WindowClosedEvent& e)
	{
		m_Running = false;
		return true;
	}
}