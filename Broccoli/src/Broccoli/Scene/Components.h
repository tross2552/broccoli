#pragma once
#include "Broccoli/Math/Math.h"

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

		Matrix4x4 TransformMatrix;

		TransformComponent() :
			TransformMatrix(Identity4x4()) {}
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Matrix4x4& transform) :
			TransformMatrix(transform) {}

		operator Matrix4x4& () { return TransformMatrix; }
		operator const Matrix4x4& () const { return TransformMatrix; }

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

}
