#pragma once
#include "Camera.h"
#include "Texture.h"
#include "Broccoli/Math/Math.h"

namespace brcl::renderer2d
{

	struct DebugStats
	{
		unsigned int DrawCalls = 0;
		unsigned int QuadCount = 0;

		unsigned int GetTotalVertexCount() { return QuadCount * 4; }
		unsigned int GetTotalIndexCount() { return QuadCount * 6; }
		
	};
	
	
	void Init();
	void Shutdown();

	void BeginScene(const Camera& camera, const Matrix4x4& transform);
	void EndScene();

	void Flush();

	void DrawQuad(const Matrix4x4& transform, const Vector4& color);
	void DrawQuad(const Matrix4x4& transform, std::shared_ptr<Texture2D> texture, const Vector4& textureParameters = { 0.0f, 0.0f, 1.0f, 1.0f });
	void DrawQuad(const Matrix4x4& transform, std::shared_ptr<Texture2D> texture, const Vector4& color, const Vector4& textureParameters);

	DebugStats GetStats();
	void ResetStats();

	
}
