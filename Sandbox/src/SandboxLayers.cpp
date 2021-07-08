#include "SandboxLayers.h"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Sandbox
{
	
	void Sandbox2DLayer::OnAttach()
	{
		m_Texture = brcl::Texture2D::Create("assets/textures/broccoli_texture_small_formatted.png");
	}

	void Sandbox2DLayer::OnDetach()
	{
	}

	void Sandbox2DLayer::OnUpdate(brcl::Timestep deltaTime)
	{
		BRCL_TRACE("Sandbox: Update ({0}) ", deltaTime.ToString());
		m_CameraController.OnUpdate(deltaTime);

		
		brcl::renderer2d::BeginScene(m_CameraController.GetCamera());

		brcl::Transform quad;
		brcl::Vector4 colorInv = 1.0f - m_Color;
		colorInv[3] = 1.0f;
		
		brcl::renderer2d::DrawQuad(quad, m_Color);
		
		quad.AbsMove(brcl::Vector3({ -1.0f, -1.0f, 0.0f }));
		quad.SetScale({ 0.5f, 1.0f, 0.0f });
		
		brcl::renderer2d::DrawQuad(quad, colorInv);

		quad.SetScale(10.0f);
		quad.SetPosition({ -5.0f, -5.0f, 0.1f });

		brcl::renderer2d::DrawQuad(quad, m_Texture);
		
		brcl::renderer::EndScene();
		
	}

	void Sandbox2DLayer::OnEvent(brcl::Event& event)
	{
		BRCL_TRACE("{0}", event);
		m_CameraController.OnEvent(event);
	}

	//--------------Engine Debug Application-----------------
	
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

		using namespace brcl;
		
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer>  indexBuffer;
		
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color"    },
			{ ShaderDataType::Float2, "a_TexCoord"    }
		};
		

		
		float vertices[3 * 9] = {
			-0.5f , -0.5f , 0.0f , 0.0f , 1.0f , 1.0f, 1.0f , 0.0f, 0.0f,
			 0.5f , -0.5f , 0.0f , 1.0f , 0.0f , 1.0f, 1.0f , 0.0f, 0.0f,
			 0.0f ,  0.5f , 0.0f , 1.0f , 1.0f , 0.0f, 1.0f , 0.0f, 0.0f
		};
		uint32_t indices[3] = { 0 , 1 , 2 };

		
		m_VertexArray = VertexArray::Create();
		vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		indexBuffer  = IndexBuffer::Create(indices, sizeof(indices));
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

		m_VertexArraySquare = VertexArray::Create();
		vertexBuffer = VertexBuffer::Create(vertices2, sizeof(vertices2));
		indexBuffer  = IndexBuffer::Create(indices2, sizeof(indices2));
		vertexBuffer->SetLayout(layout);
		m_VertexArraySquare->AddVertexBuffer(vertexBuffer);
		m_VertexArraySquare->SetIndexBuffer(indexBuffer);

		
		m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		
		m_Texture     = Texture2D::Create("assets/textures/broccoli_texture_small_formatted.png");
		m_TextureLogo = Texture2D::Create("assets/textures/logo_formatted.png");
	}

	void ExampleLayer::OnUpdate(brcl::Timestep deltaTime)
	{

		using namespace brcl;
		
		BRCL_TRACE("Sandbox: Update ({0}) ", deltaTime.ToString());
		m_CameraController.OnUpdate(deltaTime);

		RenderCommand::SetClearColor({ 1.0f , 0.0f, 1.0f, 1.0f });
		RenderCommand::Clear();

		renderer::BeginScene(m_CameraController.GetCamera());

		auto shader = m_ShaderLibrary.Get("Texture");
		
		m_Texture->Bind();
		std::dynamic_pointer_cast<brcl::OpenGLShader>(shader)->UploadUniformInt("u_Texture", 0); //todo: texture slots in shader
		renderer::Submit(shader, m_VertexArray, brcl::Identity4x4());
		std::dynamic_pointer_cast<brcl::OpenGLShader>(shader)->UploadUniformFloat4("u_Color", m_Color);

		

		renderer::Submit(shader, m_VertexArraySquare, brcl::Scale(brcl::Identity4x4(), 2.0f));
		m_TextureLogo->Bind();
		renderer::Submit(shader, m_VertexArraySquare, brcl::Scale(brcl::Identity4x4(), 2.0f));

		renderer::EndScene();


	}

	void ExampleLayer::OnEvent(brcl::Event& event)
	{
		BRCL_TRACE("{0}", event);
		m_CameraController.OnEvent(event);
	}
}