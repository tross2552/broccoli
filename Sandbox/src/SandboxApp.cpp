#include <Broccoli.h>

namespace Sandbox
{

	class ExampleLayer : public brcl::Layer
	{
	public:
		ExampleLayer();

		void OnUpdate(brcl::Timestep deltaTime) override;

		void OnEvent(brcl::Event& event) override;

	private:

		std::shared_ptr<brcl::Shader> m_Shader;

		std::shared_ptr<brcl::VertexArray> m_VertexArray;

		std::shared_ptr<brcl::VertexArray> m_VertexArraySquare;

		brcl::Camera m_Camera;
	};
	
	class Sandbox : public brcl::Application
	{
	public:
		
		Sandbox()
		{
			PushLayer(new ExampleLayer());
			PushLayer(new brcl::ImGuiLayer());
		}
	};


	ExampleLayer::ExampleLayer() :
		Layer("Example"), m_Camera(-2.0, 2.0, -2.0, 2.0)
	{
		m_VertexArray.reset(brcl::VertexArray::Create());


		std::shared_ptr<brcl::VertexBuffer> vertexBuffer;
		std::shared_ptr<brcl::IndexBuffer> indexBuffer;

		float vertices[3 * 7] = {
			-0.5f , -0.5f , 0.0f , 0.0f , 1.0f , 1.0f, 1.0f ,
			 0.5f , -0.5f , 0.0f , 1.0f , 0.0f , 1.0f, 1.0f ,
			 0.0f ,  0.5f , 0.0f , 1.0f , 1.0f , 0.0f, 1.0f
		};

		vertexBuffer.reset(brcl::VertexBuffer::Create(vertices, sizeof(vertices)));


		brcl::BufferLayout layout = {
			{ brcl::ShaderDataType::Float3, "a_Position" },
			{ brcl::ShaderDataType::Float4, "a_Color"    }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0 , 1 , 2 };

		indexBuffer.reset(brcl::IndexBuffer::Create(indices, sizeof(indices)));
		m_VertexArray->SetIndexBuffer(indexBuffer);



		m_VertexArraySquare.reset(brcl::VertexArray::Create());

		float vertices2[4 * 7] = {
			-0.7f , -0.7f , 0.0f , 0.0f , 1.0f , 1.0f, 1.0f ,
			-0.7f , -0.8f , 0.0f , 1.0f , 0.0f , 1.0f, 1.0f ,
			-0.8f , -0.8f , 0.0f , 1.0f , 1.0f , 0.0f, 1.0f ,
			-0.8f , -0.7f , 0.0f , 1.0f , 1.0f , 1.0f, 1.0f
		};

		vertexBuffer.reset(brcl::VertexBuffer::Create(vertices2, sizeof(vertices2)));

		vertexBuffer->SetLayout(layout);
		m_VertexArraySquare->AddVertexBuffer(vertexBuffer);

		uint32_t indices2[6] = { 0 , 1 , 2, 0, 2, 3 };

		indexBuffer.reset(brcl::IndexBuffer::Create(indices2, sizeof(indices2)));
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

		m_Shader.reset(new brcl::Shader(vertexSrc, fragmentSrc));
	}

	void ExampleLayer::OnUpdate(brcl::Timestep deltaTime)
	{
		
		BRCL_TRACE("Sandbox: Update ({0}) ", deltaTime.ToString());
		
		brcl::RenderCommand::SetClearColor({ 1.0f , 0.0f, 1.0f, 1.0f });
		brcl::RenderCommand::Clear();

		brcl::Renderer::BeginScene(m_Camera);

		brcl::Renderer::Submit(m_Shader, m_VertexArray);
		brcl::Renderer::Submit(m_Shader, m_VertexArraySquare);

		brcl::Renderer::EndScene();

		static bool rotateFlag;

		if (brcl::Input::IsKeyPressed(brcl::Input::BRCLKeyCodes::E)) rotateFlag = true;
		if (brcl::Input::IsKeyPressed(brcl::Input::BRCLKeyCodes::Q)) rotateFlag = false;

		if (brcl::Input::IsKeyPressed(brcl::Input::BRCLKeyCodes::W))
		{
			BRCL_CORE_INFO("UP UP UP UP !!!!!!!");
			if (!rotateFlag) m_Camera.SetPosition(m_Camera.GetPosition() + brcl::Vector3({ 0.0f, 1.0f, 0.0f }) * deltaTime);
			else m_Camera.SetRotation(m_Camera.GetRotation() + brcl::Vector3({ 0.0f,1.0f,0.0f }) * deltaTime);
		}

		if (brcl::Input::IsKeyPressed(brcl::Input::BRCLKeyCodes::A))
		{
			BRCL_CORE_INFO("LEFT LEFT LEFT LEFT !!!!!!!");
			if (!rotateFlag) m_Camera.SetPosition(m_Camera.GetPosition() + brcl::Vector3({ -1.0f, 0.0f, 0.0f }) * deltaTime);
			else m_Camera.SetRotation(m_Camera.GetRotation() + brcl::Vector3({ 1.0f,0.0f,0.0f }) * deltaTime);
		}

		if (brcl::Input::IsKeyPressed(brcl::Input::BRCLKeyCodes::S))
		{
			BRCL_CORE_INFO("DOWN DOWN DOWN DOWN !!!!!!!");
			if (!rotateFlag) m_Camera.SetPosition(m_Camera.GetPosition() + brcl::Vector3({ 0.0f, -1.0f, 0.0f }) * deltaTime);
			else m_Camera.SetRotation(m_Camera.GetRotation() + brcl::Vector3({ 0.0f,-1.0f,0.0f }) * deltaTime);
		}

		if (brcl::Input::IsKeyPressed(brcl::Input::BRCLKeyCodes::D))
		{
			BRCL_CORE_INFO("RIGHT RIGHT RIGHT RIGHT !!!!!!!");
			if (!rotateFlag) m_Camera.SetPosition(m_Camera.GetPosition() + brcl::Vector3({ 1.0f, 0.0f, 0.0f }) * deltaTime);
			else m_Camera.SetRotation(m_Camera.GetRotation() + brcl::Vector3({ -1.0f,0.0f,0.0f }) * deltaTime);
		}

		if (brcl::Input::IsKeyPressed(brcl::Input::BRCLKeyCodes::X))
		{
			m_Camera.SetPosition({ 0.0f, 0.0f, 0.0f });
			m_Camera.SetRotation({ 0.0f,0.0f,0.0f });
		}

		m_Camera.OnUpdate();


	}

	void ExampleLayer::OnEvent(brcl::Event& event)
	{
		BRCL_TRACE("{0}", event);
	}

	
}

brcl::Application* brcl::CreateApplication()
{
	return new Sandbox::Sandbox();
}