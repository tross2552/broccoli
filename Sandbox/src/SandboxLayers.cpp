#include "SandboxLayers.h"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Sandbox
{	
	void ExampleImGuiLayer::OnImGuiRender()
	{
		ImGui::Begin("Settings");
		ImGui::Text("Hello");
		ImGui::ColorEdit4("Square Color", m_AppLayer->m_Color.data());
		ImGui::End();

		ImGui::ShowDemoWindow();
	}

	ExampleLayer::ExampleLayer() :
		Layer("Example"), m_CameraController(16.0f/9.0f), m_Color(1.0f)
	{

		std::shared_ptr<brcl::VertexBuffer> vertexBuffer;
		std::shared_ptr<brcl::IndexBuffer>  indexBuffer;
		
		brcl::BufferLayout layout = {
			{ brcl::ShaderDataType::Float3, "a_Position" },
			{ brcl::ShaderDataType::Float4, "a_Color"    },
			{ brcl::ShaderDataType::Float2, "a_TexCoord"    }
		};
		

		
		float vertices[3 * 9] = {
			-0.5f , -0.5f , 0.0f , 0.0f , 1.0f , 1.0f, 1.0f , 0.0f, 0.0f,
			 0.5f , -0.5f , 0.0f , 1.0f , 0.0f , 1.0f, 1.0f , 0.0f, 0.0f,
			 0.0f ,  0.5f , 0.0f , 1.0f , 1.0f , 0.0f, 1.0f , 0.0f, 0.0f
		};
		uint32_t indices[3] = { 0 , 1 , 2 };

		
		m_VertexArray = brcl::VertexArray::Create();
		vertexBuffer = brcl::VertexBuffer::Create(vertices, sizeof(vertices));
		indexBuffer  = brcl::IndexBuffer::Create(indices, sizeof(indices));
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);


		float vertices2[4 * 9] = {
			0.0f , 0.0f , 0.0f , 0.0f , 1.0f , 1.0f, 1.0f , 0.0f, 0.0f,
			0.0f , 1.0f , 0.0f , 1.0f , 0.0f , 1.0f, 1.0f , 0.0f, 1.0f,
			1.0f , 1.0f , 0.0f , 1.0f , 1.0f , 0.0f, 1.0f , 1.0f, 1.0f,
			1.0f , 0.0f , 0.0f , 1.0f , 1.0f , 1.0f, 1.0f , 1.0f, 0.0f
		};
		uint32_t indices2[6] = { 0 , 1 , 2, 0, 2, 3 };

		m_VertexArraySquare = brcl::VertexArray::Create();
		vertexBuffer = brcl::VertexBuffer::Create(vertices2, sizeof(vertices2));
		indexBuffer  = brcl::IndexBuffer::Create(indices2, sizeof(indices2));
		vertexBuffer->SetLayout(layout);
		m_VertexArraySquare->AddVertexBuffer(vertexBuffer);
		m_VertexArraySquare->SetIndexBuffer(indexBuffer);

		
		m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		
		m_Texture     = brcl::Texture2D::Create("assets/textures/broccoli_texture_small_formatted.png");
		m_TextureLogo = brcl::Texture2D::Create("assets/textures/logo_formatted.png");
	}

	void ExampleLayer::OnUpdate(brcl::Timestep deltaTime)
	{

		BRCL_TRACE("Sandbox: Update ({0}) ", deltaTime.ToString());
		m_CameraController.OnUpdate(deltaTime);

		

		brcl::RenderCommand::SetClearColor({ 1.0f , 0.0f, 1.0f, 1.0f });
		brcl::RenderCommand::Clear();

		brcl::Renderer::BeginScene(m_CameraController.GetCamera());

		auto shader = m_ShaderLibrary.Get("Texture");
		
		m_Texture->Bind();
		std::dynamic_pointer_cast<brcl::OpenGLShader>(shader)->UploadUniformInt("u_Texture", 0); //todo: texture slots in shader
		brcl::Renderer::Submit(shader, m_VertexArray, brcl::Identity4x4());
		std::dynamic_pointer_cast<brcl::OpenGLShader>(shader)->UploadUniformFloat4("u_Color", m_Color);

		

		brcl::Renderer::Submit(shader, m_VertexArraySquare, brcl::Scale(brcl::Identity4x4(), 2.0f));
		m_TextureLogo->Bind();
		brcl::Renderer::Submit(shader, m_VertexArraySquare, brcl::Scale(brcl::Identity4x4(), 2.0f));

		brcl::Renderer::EndScene();


	}

	void ExampleLayer::OnEvent(brcl::Event& event)
	{
		BRCL_TRACE("{0}", event);
		m_CameraController.OnEvent(event);
	}
}