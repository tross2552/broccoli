#include "brclpch.h"
#include "Application.h"
#include "Broccoli/Events/ApplicationEvent.h"
#include "Broccoli/Log.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Windows/WindowsInput.h"

#include <glad/glad.h>
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

namespace brcl
{

	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_Camera(-2.0, 2.0, -2.0, 2.0)
	{
		if (!s_Instance) s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		m_VertexArray.reset(new OpenGLVertexArray());


		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;
		
		float vertices[3 * 7] = {
			-0.5f , -0.5f , 0.0f , 0.0f , 1.0f , 1.0f, 1.0f ,
			 0.5f , -0.5f , 0.0f , 1.0f , 0.0f , 1.0f, 1.0f ,
			 0.0f ,  0.5f , 0.0f , 1.0f , 1.0f , 0.0f, 1.0f
		};

		vertexBuffer.reset(new OpenGLVertexBuffer(vertices, sizeof(vertices)));

		
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color"    }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		

		uint32_t indices[3] = { 0 , 1 , 2 };

		indexBuffer.reset(new OpenGLIndexBuffer(indices, sizeof(indices)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		
		m_VertexArraySquare.reset(new OpenGLVertexArray());

		float vertices2[4 * 7] = {
			-0.7f , -0.7f , 0.0f , 0.0f , 1.0f , 1.0f, 1.0f ,
			-0.7f , -0.8f , 0.0f , 1.0f , 0.0f , 1.0f, 1.0f ,
			-0.8f , -0.8f , 0.0f , 1.0f , 1.0f , 0.0f, 1.0f ,
			-0.8f , -0.7f , 0.0f , 1.0f , 1.0f , 1.0f, 1.0f
		};

		vertexBuffer.reset(new OpenGLVertexBuffer(vertices2, sizeof(vertices2)));

		vertexBuffer->SetLayout(layout);
		m_VertexArraySquare->AddVertexBuffer(vertexBuffer);

		uint32_t indices2[6] = { 0 , 1 , 2, 0, 2, 3 };

		indexBuffer.reset(new OpenGLIndexBuffer(indices2, sizeof(indices2)));
		m_VertexArraySquare->SetIndexBuffer(indexBuffer);
		

		const std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position * 0.5 + 0.5;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		const std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4( v_Position, 1.0 );
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}
	Application::~Application()
	{

	}

	void Application::Run()
	{
		
		while (m_Running) {
			
			RenderCommand::SetClearColor({ 1.0f , 0.0f, 1.0f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene(m_Camera);
			
			Renderer::Submit(m_Shader, m_VertexArray);
			Renderer::Submit(m_Shader, m_VertexArraySquare);

			
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();

				if (Input::IsKeyPressed(Input::BRCLKeyCodes::W))
				{
					BRCL_CORE_INFO("UP UP UP UP !!!!!!!");
					m_Camera.SetPosition({ 0.0f, 1.0f, 0.0f });
				}
				
				if (Input::IsKeyPressed(Input::BRCLKeyCodes::A))
				{
					BRCL_CORE_INFO("LEFT LEFT LEFT LEFT !!!!!!!");
					m_Camera.SetPosition({ -0.5f, -0.5f, 0.0f });
				}
				
				if (Input::IsKeyPressed(Input::BRCLKeyCodes::S))
				{
					BRCL_CORE_INFO("DOWN DOWN DOWN DOWN !!!!!!!");
					m_Camera.SetPosition({ 0.0f, 0.0f, 0.0f });
				}
				
				if (Input::IsKeyPressed(Input::BRCLKeyCodes::D))
				{
					BRCL_CORE_INFO("RIGHT RIGHT RIGHT RIGHT !!!!!!!");
					m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
				}
				

				m_Camera.OnUpdate();
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