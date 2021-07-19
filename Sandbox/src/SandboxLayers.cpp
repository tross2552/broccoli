#include "SandboxLayers.h"
#include "imgui/imgui.h"

namespace Sandbox
{
	
	void SandboxLayer::OnAttach()
	{
		m_Texture = brcl::Texture2D::Create("assets/textures/broccoli_texture_small_formatted.png");

		brcl::FrameBufferSpec fBufferSpec;
		fBufferSpec.Width = 1280;
		fBufferSpec.Height = 720;
		m_Framebuffer = brcl::Framebuffer::Create(fBufferSpec);
	}

	void SandboxLayer::OnDetach()
	{
	}

	void SandboxLayer::OnUpdate(brcl::Timestep deltaTime)
	{
		BRCL_TRACE("Editor: Update ({0}) ", deltaTime.ToString());
		m_CameraController.OnUpdate(deltaTime);
		
		static float rotation = 0.0f;
		rotation += 0.01f;

		brcl::renderer2d::ResetStats();
		brcl::renderer2d::BeginScene(m_CameraController.GetCamera(), m_CameraController.GetTransform().GetMatrix());
		brcl::Transform quad;
		brcl::Vector4 colorInv = 1.0f - m_Color;
		colorInv[3] = 1.0f;
		
		quad.SetPosition({ 0.0f,0.0f,0.0f });
		quad.SetScale(1.0f);
		brcl::renderer2d::DrawQuad(quad, m_Color);
		
		quad.SetPosition({ -1.0f, -1.0f, 0.0f });
		quad.SetScale({ 0.5f, 1.0f, 0.0f });
		brcl::renderer2d::DrawQuad(quad, colorInv);

		
		quad.SetPosition({ -5.0f, -5.0f, 0.2f });
		quad.SetScale(0.5f);
		brcl::renderer2d::DrawQuad(quad, m_Texture, m_TexParams);

		quad.SetPosition({ -1.0f, -1.0f, 0.3f });
		quad.SetRotation({ 0.0f, 0.0f, 0.0f });
		quad.SetScale(2.0f);
		brcl::renderer2d::DrawQuad(quad, m_Texture, m_TexParams*2);

		quad.SetPosition({ -1.0f, -1.0f, 0.4f });
		quad.SetRotation({ 0.0f,0.0f, rotation });
		brcl::renderer2d::DrawQuad(quad, m_Texture, m_TexParams * 2);

		quad.SetPosition({ -5.0f, -5.0f, 0.5f });
		quad.SetRotation({ 0.0f,0.0f, -rotation });
		quad.SetScale(1.0f);
		brcl::renderer2d::DrawQuad(quad, m_Texture, m_TexParams);
		
		
		brcl::renderer2d::EndScene();
		
	}

	bool SandboxLayer::OnResize(brcl::WindowResizedEvent& event) //todo: move this back into the engine
	{
		brcl::renderer::ResizeViewport(event.GetWidth(), event.GetHeight());
		return true;
	}

	void SandboxLayer::OnEvent(brcl::Event& event)
	{
		BRCL_TRACE("{0}", event);
		m_CameraController.OnEvent(event);
		brcl::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<brcl::WindowResizedEvent>(BRCL_BIND_EVENT_FN(SandboxLayer::OnResize));
		
	}

	//--------------Engine Debug Application-----------------
	
	void ExampleImGuiLayer::OnImGuiRender()
	{
		static auto renderdebug = brcl::renderer2d::GetStats();
		renderdebug = brcl::renderer2d::GetStats();
		
		ImGui::Begin("Settings");
		ImGui::Text("Hello");
		ImGui::Text("Draw Calls: %d", renderdebug.DrawCalls);
		ImGui::Text("Quads: %d", renderdebug.QuadCount);
		ImGui::Text("Vertices: %d", renderdebug.GetTotalVertexCount());
		ImGui::Text("Indices: %d", renderdebug.GetTotalIndexCount());
		ImGui::ColorEdit4("Square Color", m_AppLayer->m_Color.data());
		ImGui::DragFloat4("Checker Texture", m_AppLayer->m_TexParams.data(), 0.01f, 0.0f, 20.0f);
		ImGui::End();

		ImGui::ShowDemoWindow();
	}

	void ExampleImGuiLayer::OnEvent(brcl::Event& event)
	{

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
		
		BRCL_TRACE("Editor: Update ({0}) ", deltaTime.ToString());
		m_CameraController.OnUpdate(deltaTime);

		RenderCommand::SetClearColor({ 1.0f , 0.0f, 1.0f, 1.0f });
		RenderCommand::Clear();

		renderer::BeginScene(m_CameraController.GetCamera());

		auto shader = m_ShaderLibrary.Get("Texture");
		
		m_Texture->Bind();
		shader->SetUniformInt("u_Texture", 0); //todo: texture slots in shader
		renderer::Submit(shader, m_VertexArray, brcl::Identity4x4());
		shader->SetUniformFloat4("u_Color", m_Color);

		

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