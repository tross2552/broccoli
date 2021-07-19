#pragma once
#include "Broccoli/Math/Math.h"
#include "Broccoli/Renderer/Camera.h"
#include "Broccoli/Transform.h"

namespace brcl
{

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) :
			Tag(tag) {}
	};
	
	struct TransformComponent
	{

		Transform MyTransform; //todo: collapse transform into this struct

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		
		operator Matrix4x4 () const { return MyTransform.GetMatrix(); }

	};

	struct SpriteRendererComponent
	{

		Vector4 ColorVector;

		SpriteRendererComponent() :
			ColorVector(1.0f) {}
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const Vector4& transform) :
			ColorVector(transform)
		{
		}

		operator Vector4& () { return ColorVector; }
		operator const Vector4& () const { return ColorVector; }

	};

	struct CameraComponent
	{
		Camera MyCamera;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(float aspectRatio) :
			MyCamera(aspectRatio) {}
		CameraComponent(const Matrix4x4& projection) :
			MyCamera(projection) {}
	};

}
