#include "brclpch.h"
#include "Renderer2D.h"

#include "Texture.h"
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
		std::shared_ptr<Shader> FlatTextureShader;
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

		s_Data->FlatColorShader   = Shader::Create("assets/shaders/FlatColor.glsl");
		s_Data->FlatTextureShader = Shader::Create("assets/shaders/FlatTexture.glsl");

		s_Data->FlatTextureShader->Bind();
		s_Data->FlatTextureShader->SetUniformInt("u_Texture", 0);
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
		s_Data->FlatColorShader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data->FlatTextureShader->Bind();
		s_Data->FlatTextureShader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void EndScene()
	{
	}

	void DrawQuad(const Transform& transform, const Vector4& color)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetUniformFloat4("u_Color", color);


		s_Data->FlatColorShader->SetUniformMat4("u_Transform", transform.GetMatrix());

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void DrawQuad(const Transform& transform, std::shared_ptr<Texture2D> texture)
	{
		s_Data->FlatTextureShader->Bind();
		texture->Bind();


		s_Data->FlatTextureShader->SetUniformMat4("u_Transform", transform.GetMatrix());

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	
	
}
