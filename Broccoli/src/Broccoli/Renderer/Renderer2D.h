#pragma once
#include "Camera.h"
#include "Broccoli/Math/Math.h"

namespace brcl::renderer2d
{
	void Init();
	void Shutdown();

	void BeginScene(const Camera& camera);
	void EndScene();

	void DrawQuad(const Vector2& position, const Vector2& size, const Vector4& color);
	void DrawQuad(const Vector3& position, const Vector2& size, const Vector4& color);
}
