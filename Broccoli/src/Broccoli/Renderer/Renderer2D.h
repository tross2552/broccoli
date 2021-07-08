#pragma once
#include "Camera.h"
#include "Texture.h"
#include "Broccoli/Math/Math.h"

namespace brcl::renderer2d
{
	void Init();
	void Shutdown();

	void BeginScene(const Camera& camera);
	void EndScene();

	void DrawQuad(const Transform& transform, const Vector4& color);
	void DrawQuad(const Transform& transform, std::shared_ptr<Texture2D> texture);
}
