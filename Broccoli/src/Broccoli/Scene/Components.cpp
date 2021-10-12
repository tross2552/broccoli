#include "brclpch.h"
#include "Components.h"

#include "Broccoli/Physics/SimplePhysicsEngine2D.h"

namespace brcl
{
	void RigidBodyComponent::SetVelocity(entt::entity handle, Vector2 velocity)
	{
		this->velocity = velocity;
		SimplePhysicsEngine2D::SetVelocity(handle, velocity);
	}
}
