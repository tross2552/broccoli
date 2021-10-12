#include "brclpch.h"
#include "Renderer2D.h"

#include "Texture.h"
#include "Broccoli/Renderer/Shader.h"
#include "Broccoli/Renderer/VertexArray.h"
#include "Broccoli/Renderer/RenderCommand.h"

#include <array>

namespace brcl::renderer2d
{

	constexpr int max_draw_quads = 15000;
	constexpr int max_draw_vertices = max_draw_quads * 4;
	constexpr int max_draw_indices = max_draw_quads * 6;
	constexpr int max_draw_textures = 32;
	
	struct Vertex2D
	{
		float x,y,z;
		float r,g,b,a;
		float u, v;
		float texslot;
	};
	
	//todo: determine best way to store renderer data
	struct Renderer2DStorage
	{
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<Shader> FlatTextureShader;
		//std::shared_ptr<Texture2D> FlatColorTexture;

		std::shared_ptr<VertexBuffer> VertexBuffer;

		std::shared_ptr<std::array<Vertex2D, max_draw_vertices>> Vertices;
		std::shared_ptr<std::array<uint32_t, max_draw_indices>> Indices;

		std::array<std::shared_ptr<Texture2D>, max_draw_textures> TextureSlots;

		int32_t TexturesUsed;
		unsigned int QuadsDrawn;

		RenderDebugStats2D stats;
	};

	static Renderer2DStorage* s_Data;

	
	void Init()
	{

		s_Data = new Renderer2DStorage();
		
		std::shared_ptr<IndexBuffer>  indexBuffer;

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color"    },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float , "a_TexSlot"  }
		};

		s_Data->Vertices = std::make_shared<std::array<Vertex2D, max_draw_vertices>>();

		float vertices2[4 * 7] = {
			0.0f , 0.0f , 0.0f , 1.0f , 1.0f , 1.0f , 1.0f ,
			0.0f , 1.0f , 0.0f , 1.0f , 1.0f , 1.0f , 1.0f ,
			1.0f , 1.0f , 0.0f , 1.0f , 1.0f , 1.0f , 1.0f ,
			1.0f , 0.0f , 0.0f , 1.0f , 1.0f , 1.0f , 1.0f
		};

		s_Data->Indices = std::make_shared<std::array<uint32_t, max_draw_indices>>();

		uint32_t quad = 0;
		for(int q = 0; q < max_draw_quads; q++)
		{
			(*s_Data->Indices)[q * 6 + 0] = q*4+0;
			(*s_Data->Indices)[q * 6 + 1] = q*4+1;
			(*s_Data->Indices)[q * 6 + 2] = q*4+2;
			(*s_Data->Indices)[q * 6 + 3] = q*4+0;
			(*s_Data->Indices)[q * 6 + 4] = q*4+2;
			(*s_Data->Indices)[q * 6 + 5] = q*4+3;
		}
		s_Data->QuadVertexArray = VertexArray::Create();
		s_Data->VertexBuffer = VertexBuffer::Create(sizeof(*s_Data->Vertices));
		indexBuffer = IndexBuffer::Create(s_Data->Indices->data(), sizeof(*s_Data->Indices));
		s_Data->VertexBuffer->SetLayout(layout);
		s_Data->QuadVertexArray->AddVertexBuffer(s_Data->VertexBuffer);
		s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);
		
		s_Data->FlatTextureShader = Shader::Create("assets/shaders/FlatTexture.glsl");

		s_Data->TextureSlots[0] = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->TextureSlots[0]->SetData(&whiteTextureData, 4);
		s_Data->TexturesUsed = 1;
		
		s_Data->FlatTextureShader->Bind();
		//s_Data->FlatTextureShader->SetUniformInt("u_Texture", 0);

		std::array<int32_t, max_draw_textures> samplers;
		for (int32_t i = 0; i < max_draw_textures; i++) samplers[i] = i;
		s_Data->FlatTextureShader->SetUniformIntArray("u_Textures", samplers.data(), max_draw_textures);
	}

	void Shutdown()
	{
		delete s_Data;
	}
	
	void BeginScene(const Camera& camera, const Matrix4x4& transform)
	{
		RenderCommand::SetClearColor({ 0.1f , 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		s_Data->QuadsDrawn = 0;
		s_Data->TexturesUsed = 1;

		s_Data->FlatTextureShader->Bind();
		
		auto mat = camera.GetProjectionMatrix() * Invert(transform);
		s_Data->FlatTextureShader->SetUniformMat4("u_ViewProjection", mat);
	}

	void EndScene()
	{
		Flush();
	}

	void StartBatch()
	{
		BRCL_CORE_TRACE("Renderer2d: Starting new batch");
		if (s_Data->QuadsDrawn) Flush();
		s_Data->QuadsDrawn = 0;
		s_Data->TexturesUsed = 1;
	}

	void Flush()
	{
		
		s_Data->VertexBuffer->SetData(s_Data->Vertices->data(), sizeof(*s_Data->Vertices));
		
		for (int32_t i = 0; i < s_Data->TexturesUsed; i++)
		{
			s_Data->TextureSlots[i]->Bind(i);
		}
			
		
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray, s_Data->QuadsDrawn*6);

		s_Data->stats.DrawCalls++;
	}

	void DrawQuad(const Matrix4x4& transform, std::shared_ptr<Texture2D> texture, const Vector4& textureParameters)
	{
		DrawQuad(transform, texture, Vector4({ 1.0f, 1.0f, 1.0f, 1.0f }), textureParameters);
	}

	void DrawQuad(const Matrix4x4& transform, const Vector4& color)
	{

		DrawQuad(transform, s_Data->TextureSlots[0], color, Vector4({ 0.0f, 0.0f, 1.0f, 1.0f }));
	}

	void DrawQuad(const Matrix4x4& transform, std::shared_ptr<Texture2D> texture, const Vector4& color, const Vector4& textureParameters)
	{

		if (s_Data->QuadsDrawn == max_draw_quads)
		{
			BRCL_CORE_WARN("Renderer2d Warning: Exceeded max quads per batch (Quad {0})!", s_Data->QuadsDrawn+1);
			StartBatch();
		}

		float texIndex = 0;

		for (int32_t i = 0; i < s_Data->TexturesUsed; i++)
		{
			if (*texture == *s_Data->TextureSlots[i]) texIndex = (float)i;
		}

		if (!texIndex && !(s_Data->TexturesUsed < max_draw_textures))
		{
			BRCL_CORE_WARN("Renderer2d Warning: Exceeded max textures per batch (Quad {0})!", s_Data->QuadsDrawn + 1);
			StartBatch();
		}

		if (!texIndex)
		{
			s_Data->TextureSlots[s_Data->TexturesUsed] = texture;
			texIndex = (float)s_Data->TexturesUsed;
			s_Data->TexturesUsed++;
		}
		
		Matrix4x4 quadPositions = {
			{ 0.0f,1.0f,1.0f,0.0f },
			{ 0.0f,0.0f,1.0f,1.0f },
			{ 0.0f,0.0f,0.0f,0.0f },
			{ 1.0f,1.0f,1.0f,1.0f }
		};

		std::array<float, 8> texCoords = { {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		} };

		quadPositions = transform * quadPositions;

		auto& [r, g, b, a] = color;
		Vertex2D quadVertex = { 0, 0, 0, r , g, b, a, 0.0f, 0.0f, texIndex };

		for (int i = 0; i < 4; i++)
		{
			quadVertex.x = quadPositions(0, i);
			quadVertex.y = quadPositions(1, i);
			quadVertex.z = quadPositions(2, i);
			quadVertex.u = texCoords[i * 2] * textureParameters[2] + textureParameters[0];
			quadVertex.v = texCoords[i * 2 + 1] * textureParameters[3] + textureParameters[1];

			(*s_Data->Vertices)[s_Data->QuadsDrawn * 4 + i] = quadVertex;
		}

		s_Data->QuadsDrawn++;
		s_Data->stats.QuadCount++;
	}

	RenderDebugStats2D GetStats()
	{
		return s_Data->stats;
	}

	void ResetStats()
	{
		s_Data->stats.QuadCount = 0;
		s_Data->stats.DrawCalls = 0;
	}
	
	
}
