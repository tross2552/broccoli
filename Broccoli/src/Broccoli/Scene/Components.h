#pragma once
#include "Broccoli/Math/Math.h"
#include "Broccoli/Renderer/Camera.h"
#include "Broccoli/Transform.h"
#include "Broccoli/Renderer/Texture.h"

namespace entt {
	enum class entity : std::uint32_t;
}

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

	struct CameraComponent
	{
		Camera MyCamera;
		
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(float aspectRatio) :
			MyCamera(aspectRatio) {}
		CameraComponent(const Matrix4x4& projection) :
			MyCamera(projection) {}
	};

	struct SpriteRendererComponent
	{

		Vector4 ColorVector;
		Vector4 TextureTransform;

		SpriteRendererComponent() :
			ColorVector(1.0f), TextureTransform{ 0.0f,0.0f,1.0f,1.0f } {}
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const Vector4& color, const Vector4& texTransform = { 0.0f,0.0f,1.0f,1.0f }) :
			ColorVector(color), TextureTransform(texTransform)
		{
		}

		operator Vector4& () { return ColorVector; }
		operator const Vector4& () const { return ColorVector; }

	};

	struct CircleColliderComponent
	{
		Vector2 position;
		float radius;
	};

	struct BoxColliderComponent
	{
		
		Vector2 position;
		Vector2 size;
	};

	struct RigidBodyComponent
	{
		enum class SimulationType
		{
			Dynamic,
			Static,
			Kinematic
		};

		RigidBodyComponent()  :
			simType(SimulationType::Dynamic), position(Vector2{0,0}), velocity(Vector2{0,0}), mass(0) {}

		SimulationType simType;
		Vector2 position;
		Vector2 velocity;
		float mass;
		

		void SetVelocity(entt::entity handle, Vector2 veloctiy);
		
	};
}
