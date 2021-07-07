#include "brclpch.h"
#include "Renderer2D.h"

#include "Broccoli/Renderer/Shader.h"
#include "Broccoli/Renderer/VertexArray.h"
#include "Broccoli/Renderer/RenderCommand.h"

namespace brcl::renderer2d
{

	//todo: determine best way to store renderer data
	struct Renderer2DStorage
	{
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Data;

	
	void Init()
	{

		s_Data = new Renderer2DStorage();
		
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer>  indexBuffer;

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" }
		};

		float vertices2[4 * 3] = {
			0.0f , 0.0f , 0.0f ,
			0.0f , 1.0f , 0.0f ,
			1.0f , 1.0f , 0.0f ,
			1.0f , 0.0f , 0.0f
		};
		uint32_t indices2[6] = { 0 , 1 , 2, 0, 2, 3 };

		s_Data->QuadVertexArray = VertexArray::Create();
		vertexBuffer = VertexBuffer::Create(vertices2, sizeof(vertices2));
		indexBuffer = IndexBuffer::Create(indices2, sizeof(indices2));
		vertexBuffer->SetLayout(layout);
		s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);
		s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

		s_Data->FlatColorShader = brcl::Shader::Create("assets/shaders/FlatColor.glsl");
		
	}

	void Shutdown()
	{
		delete s_Data;
	}
	
	void BeginScene(const Camera& camera)
	{
		RenderCommand::SetClearColor({ 0.1f , 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();
		
		s_Data->FlatColorShader->Bind();
		//TODO: Shader::SetUniform()
		s_Data->FlatColorShader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void EndScene()
	{
	}
	
	void DrawQuad(const Vector2& position, const Vector2& size, const Vector4& color)
	{
		DrawQuad(Vector3({position[0], position[1], 0.0f}), size, color);
	}

	void DrawQuad(const Vector3& position, const Vector2& size, const Vector4& color)
	{
		s_Data->FlatColorShader->Bind();
		//TODO: Shader::SetUniform()
		s_Data->FlatColorShader->SetUniformFloat4("u_Color", color);

		
		s_Data->FlatColorShader->SetUniformMat4("u_Transform", Translate(Identity4x4(), position) * Scale(Identity4x4(), size)); //todo: per-quad transforms

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
	
}
